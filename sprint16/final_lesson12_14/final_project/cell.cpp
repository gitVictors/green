#include "cell.h"
#include "sheet.h"

#include <cassert>
#include <iostream>
#include <string>
#include <optional>
#include <memory>

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

        // Если есть кэшированное значение, возвращаем его
        if (cached_value_.has_value()) {
            return cached_value_.value();
        }

        try {
            auto result = formula_->Evaluate(sheet_);

            // Конвертируем Formula::Value в Cell::Value
            if (std::holds_alternative<double>(result)) {
                cached_value_ = std::get<double>(result);
            } else {
                cached_value_ = std::get<FormulaError>(result);
            }
        } catch (const FormulaError& e) {
            cached_value_ = e;
        } catch (const std::exception&) {
            cached_value_ = FormulaError(FormulaError::Category::Value);
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

// Реализация методов Cell
// Cell::Cell(Sheet& sheet)
//     : impl_(std::make_unique<EmptyImpl>())
//     , sheet_(sheet) {}

Cell::Cell(Sheet& sheet)
    : impl_(std::make_unique<EmptyImpl>())
    , sheet_(sheet) {}

Cell::~Cell() = default;

void Cell::Set(std::string text) {
    if (text.empty()) {
        impl_ = std::make_unique<EmptyImpl>();
        return;
    }
    
    // Проверяем, является ли текст формулой
    if (text[0] == FORMULA_SIGN && text.length() > 1) {
        // Это формула
            std::string formula_expression = text.substr(1);
            // impl_ = std::make_unique<FormulaImpl>(std::move(formula_expression));
            impl_ = std::make_unique<FormulaImpl>(std::move(formula_expression), (SheetInterface&) sheet_);

    } else if (text[0] == ESCAPE_SIGN) {
        // Экранированный текст
        impl_ = std::make_unique<TextImpl>(std::move(text));
    } else {
        // Обычный текст
        impl_ = std::make_unique<TextImpl>(std::move(text));
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
    // return Position{0, 0}; // Заглушка - в реальной реализации нужно хранить позицию
}

void Cell::UpdateDependencies(const std::vector<Position>& new_deps) {
    // TODO: реализовать обновление зависимостей
}

bool Cell::WouldCreateCycle(const Position& pos, std::unordered_set<Position, PositionHash>& visited) const {
    // TODO: реализовать проверку циклических зависимостей
    return false;
}

void Cell::CheckCircularDependencies(const std::vector<Position>& new_deps) const {
    // TODO: реализовать проверку циклических зависимостей
}
