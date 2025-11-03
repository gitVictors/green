#include "cell.h"

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
    explicit FormulaImpl(std::string expression)
        : formula_(ParseFormula(std::move(expression))) {}

    Value GetValue() const override {
        auto result = formula_->Evaluate();

        // Конвертируем Formula::Value в Cell::Value
        if (std::holds_alternative<double>(result)) {
            return std::get<double>(result);
        } else {
            return std::get<FormulaError>(result);
        }
    }

    std::string GetText() const override {
        return FORMULA_SIGN + formula_->GetExpression();
    }

private:
    std::unique_ptr<FormulaInterface> formula_;
};

// Реализация методов Cell
Cell::Cell() : impl_(std::make_unique<EmptyImpl>()) {}

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
            impl_ = std::make_unique<FormulaImpl>(std::move(formula_expression));


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
