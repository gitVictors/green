#include "cell.h"
#include "sheet.h"

#include <cassert>
#include <iostream>
#include <string>
#include <optional>
#include <memory>
#include <cmath>

// Базовый класс для реализации ячейки
class Cell::Impl {
public:
    virtual ~Impl() = default;
    virtual Value GetValue() const = 0;
    virtual std::string GetText() const = 0;
    virtual std::vector<Position> GetReferencedCells() const { return {}; }
    virtual void InvalidateCache() {}
};

// Пустая ячейка
class Cell::EmptyImpl : public Impl {
public:
    Value GetValue() const override {
        return "";
    }
    
    std::string GetText() const override {
        return "";
    }
};

// Текстовая ячейка
class Cell::TextImpl : public Impl {
public:
    explicit TextImpl(std::string text) : text_(std::move(text)) {}
    
    Value GetValue() const override {
        // Если текст начинается с апострофа, убираем его для значения
        if (!text_.empty() && text_[0] == ESCAPE_SIGN) {
            return text_.substr(1);
        }
        return text_;
    }
    
    std::string GetText() const override {
        return text_;
    }
    
private:
    std::string text_;
};

// Формульная ячейка
class Cell::FormulaImpl : public Impl {
public:
    // explicit FormulaImpl(std::string expression)
    //     : formula_(ParseFormula(std::move(expression))) {}

    explicit FormulaImpl(std::string expression, SheetInterface& sheet)
        : formula_(ParseFormula(std::move(expression)))
        , sheet_(sheet) {}
    

    Value GetValue() const override {

        if (cached_value_.has_value()) {
            return cached_value_.value();
        }

        auto result = formula_->Evaluate(sheet_);

        if (std::holds_alternative<double>(result)) {
            double value = std::get<double>(result);

            // проверяем специальные значения
            if (std::isinf(value)) {
                // Бесконечность = арифметическая ошибка
                cached_value_ = FormulaError(FormulaError::Category::Arithmetic);
            } else if (std::isnan(value)) {
                // NaN = арифметическая ошибка (0/0)
                cached_value_ = FormulaError(FormulaError::Category::Arithmetic);
            } else {
                cached_value_ = value;
            }
        } else {
            // Уже FormulaError
            cached_value_ = std::get<FormulaError>(result);
        }

        return cached_value_.value();
    }
    
    std::string GetText() const override {
        return FORMULA_SIGN + formula_->GetExpression();
    }

    std::vector<Position> GetReferencedCells() const override {
        return formula_->GetReferencedCells();
    }

    void InvalidateCache() override {
        cached_value_.reset();
    }
    
private:
    std::unique_ptr<FormulaInterface> formula_;
    SheetInterface& sheet_;
    mutable std::optional<Value> cached_value_;
};



Cell::Cell(Sheet& sheet, Position pos)
    : impl_(std::make_unique<EmptyImpl>())
    , sheet_(sheet)
    , position_(pos)
{}

Cell::~Cell() = default;


void Cell::Set(std::string text) {

    if (text.empty()) {
        impl_ = std::make_unique<EmptyImpl>();
        // Обновляем зависимости (удаляем все старые)
        UpdateDependencies({});
        return;
    }

    // Создаем временную копию текущего состояния
    auto old_impl = std::move(impl_);
    auto old_dependencies = dependencies_;

    try {
        // Проверяем, является ли текст формулой
        if (text[0] == FORMULA_SIGN && text.length() > 1) {
            // Это формула
            std::string formula_expression = text.substr(1);

            // Создаем временную реализацию формулы для проверки зависимостей
            auto temp_formula_impl = std::make_unique<FormulaImpl>(formula_expression, (SheetInterface&)sheet_);

            // Получаем ссылки зависимостей
            std::vector<Position> new_deps = temp_formula_impl->GetReferencedCells();

            // Проверить циклические зависимости
            CheckCircularDependencies(new_deps);


            impl_ = std::move(temp_formula_impl);

            // Обновляем граф зависимостей
            UpdateDependencies(new_deps);

        } else if (text[0] == ESCAPE_SIGN) {

            impl_ = std::make_unique<TextImpl>(std::move(text));
            // Обновляем зависимости (удаляем все старые)
            UpdateDependencies({});
        } else {
            // Обычный текст
            impl_ = std::make_unique<TextImpl>(std::move(text));
            // Обновляем зависимости (удаляем все старые)
            UpdateDependencies({});
        }

        // Инвалидируем кэш и зависимые ячейки
        InvalidateCache();

        // Обновляем размеры таблицы при необходимости
        // (это должно быть реализовано в классе Sheet)

    } catch (const std::exception& e) {
        // В случае ошибки восстанавливаем предыдущее состояние
        impl_ = std::move(old_impl);
        dependencies_ = old_dependencies;
        throw; // Пробрасываем исключение дальше
    }
}


void Cell::Clear() {
    impl_ = std::make_unique<EmptyImpl>();
}

Cell::Value Cell::GetValue() const {
    return impl_->GetValue();
}

std::string Cell::GetText() const {
    return impl_->GetText();
}


std::vector<Position> Cell::GetReferencedCells() const {
    return impl_->GetReferencedCells();
}

void Cell::AddDependent(Position pos) {
    dependents_.insert(pos);
}

void Cell::RemoveDependent(Position pos) {
    dependents_.erase(pos);
}

void Cell::InvalidateCache() {
    cache_is_valid_ = false;
    cached_value_.reset();
    impl_->InvalidateCache();

    // Инвалидируем все зависимые ячейки
    for (const auto& dependent : dependents_) {
        if (auto* cell = sheet_.GetCell(dependent)) {
            if (auto* concrete_cell = dynamic_cast<Cell*>(cell)) {
                concrete_cell->InvalidateCache();
            }
        }
    }
}

bool Cell::IsCacheValid() const {
    return cache_is_valid_;
}

Position Cell::GetPosition() const {
    return position_;
}

void Cell::UpdateDependencies(const std::vector<Position>& new_deps) {
    // Удаляем старые зависимости
    for (const auto& old_dep : dependencies_) {
        if (auto* cell = sheet_.GetCell(old_dep)) {
            if (auto* concrete_cell = dynamic_cast<Cell*>(cell)) {
                concrete_cell->RemoveDependent(GetPosition());
            }
        }
    }

    // Очищаем старые зависимости
    dependencies_.clear();

    // Добавляем новые зависимости
    for (const auto& new_dep : new_deps) {
        // Создаем ячейку, если она не существует
        if (!sheet_.GetCell(new_dep)) {
            sheet_.SetCell(new_dep, "");
        }

        if (auto* cell = sheet_.GetCell(new_dep)) {
            if (auto* concrete_cell = dynamic_cast<Cell*>(cell)) {
                concrete_cell->AddDependent(GetPosition());
                dependencies_.insert(new_dep);
            }
        }
    }
}

bool Cell::WouldCreateCycle(const Position& pos, std::unordered_set<Position, PositionHash>& visited) const {
    // Если достигли текущей ячейки - цикл найден
    if (pos == GetPosition()) {
        return true;
    }

    // Если уже посещали эту позицию - пропускаем
    if (visited.count(pos)) {
        return false;
    }

    visited.insert(pos);

    // Получаем ячейку по позиции
    if (auto* cell = sheet_.GetCell(pos)) {
        if (auto* concrete_cell = dynamic_cast<Cell*>(cell)) {
            // Рекурсивно проверяем все зависимости этой ячейки
            for (const auto& dep : concrete_cell->GetReferencedCells()) {
                if (WouldCreateCycle(dep, visited)) {
                    return true;
                }
            }
        }
    }

    return false;
}

void Cell::CheckCircularDependencies(const std::vector<Position>& new_deps) const {
    std::unordered_set<Position, PositionHash> visited;

    for (const auto& dep : new_deps) {
        if (WouldCreateCycle(dep, visited)) {
            throw CircularDependencyException("Обнаружена циклическая зависимость");
        }
    }
}
