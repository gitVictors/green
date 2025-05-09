#pragma once

#include <string>
#include <sstream>
#include "calculator.h"
#include "mainwindow.h"
#include "rational.h"

template<class T>
std::string ToString(T number) {
    std::ostringstream tmp_str;
    tmp_str << number;
    return tmp_str.str();
}

template<class T>
T FromString(const std::string& number) {
    std::istringstream tmp_str{number};
    T result{};
    tmp_str >> result;
    return result;
}

inline std::string ToString(std::uint8_t number) {
    std::ostringstream tmp_str;
    tmp_str << +number;
    return tmp_str.str();
}

template<>
std::uint8_t FromString<std::uint8_t>(const std::string& number) {
    std::istringstream tmp_str{number};
    unsigned result{};
    tmp_str >> result;
    return static_cast<std::uint8_t>(result);
}

template<class Number>
class Controller
{
public:
    Controller() {}

    void BindWithMainWindow(MainWindow* main_window) {
        view_ = main_window;
        if (!view_) {
            return;
        }

        view_->SetDigitKeyCallback([this](int key){
            PressDigitKey(key);
        });
        view_->SetProcessOperationKeyCallback([this](Operation key){
            ProcessOperationKey(key);
        });
        view_->SetProcessControlKeyCallback([this](ControlKey key){
            ProcessControlKey(key);
        });

        RevealView();
    }

private:
    void PressDigitKey(int digit) {
        AddChar(digit + '0');
    }

    void ProcessOperationKey(Operation operation) {
        switch(operation) {
        case Operation::ADDITION:
            OnOperation([this](Number x){return calculator_.Add(x);}, " + ");
            break;
        case Operation::SUBTRACTION:
            OnOperation([this](Number x){return calculator_.Sub(x);}, " − ");
            break;
        case Operation::MULTIPLICATION:
            OnOperation([this](Number x){return calculator_.Mul(x);}, " × ");
            break;
        case Operation::DIVISION:
            OnOperation([this](Number x){return calculator_.Div(x);}, " ÷ ");
            break;
        case Operation::POWER:
            OnOperation([this](Number x){return calculator_.Pow(x);}, " ^ ");
            break;
        }
    }

    void ProcessControlKey(ControlKey key) {
        switch(key) {
        case ControlKey::EQUALS: {
            if (!operation_) {
                return;
            }
            std::string formula = ToString(calculator_.GetNumber()) + operation_name_ + ToString(active_number_) + " = ";

            auto error = operation_(active_number_);
            if (error.has_value()) {
                SetErrorInView(error.value());
                break;
            }

            SetFormulaInView(formula);
            SetInputAsNumber(calculator_.GetNumber());
            operation_ = {};
            break;
        }
        case ControlKey::CLEAR:
            SetInputAsNumber(Number{});
            SetFormulaInView("");
            operation_ = {};
            break;
        case ControlKey::MEM_SAVE:
            mem_ = active_number_;
            SetMemInView("M");
            break;
        case ControlKey::MEM_LOAD:
            if (!mem_.has_value()) {
                return;
            }
            SetInputAsNumber(mem_.value());
            SetFormulaInView("");
            break;
        case ControlKey::MEM_CLEAR:
            mem_ = std::nullopt;
            SetMemInView("");
            break;
        case ControlKey::PLUS_MINUS:
            if (input_as_number_) {
                active_number_ = -active_number_;
                SetInputAsNumber(active_number_);
            } else {
                if (input_.size() && input_.front() == '-') {
                    SetInputAsString(input_.substr(1));
                } else {
                    SetInputAsString("-" + input_);
                }
            }
            break;
        case ControlKey::BACKSPACE:
            if (input_.size() > 0) {
                SetInputAsString(input_.substr(0, input_.size() - 1));
            }
            break;
        case ControlKey::EXTRA_KEY:
            DoExtraAction();
            break;
        }
    }

    std::optional<std::string> GetExtraKey() const {
        if constexpr (std::is_integral_v<Number>) {
            return std::nullopt;
        }
        if constexpr (std::is_same_v<Number, Rational>) {
            return "/";
        }
        return ".";
    }

    void OnOperation(std::function<std::optional<Error> (Number)> action, std::string text) {
        if (!operation_) {
            calculator_.Set(active_number_);
        }

        operation_name_ = text;
        operation_ = action;
        input_ = "";

        SetFormulaInView(ToString(calculator_.GetNumber()) + text);
    }

    void SetInputAsString(const std::string& new_input) {
        input_as_number_ = false;
        input_ = new_input;
        active_number_ = FromString<Number>(input_);
        UpdateInputInView(new_input);
    }

    void SetInputAsNumber(Number number) {
        input_as_number_ = true;
        input_ = "";
        active_number_ = number;
        UpdateInputInView(ToString(active_number_));
    }

    void AddChar(char character) {
        SetInputAsString(input_ + character);
    }

    void DoExtraAction() {
        if constexpr (std::is_integral_v<Number>) {
            return;
        }
        if constexpr (std::is_same_v<Number, Rational>) {
            if (input_.size() == 0 || input_.find('/') != std::string::npos) {
                return;
            }
            AddChar('/');
        } else {
            if (input_.find('.') != std::string::npos) {
                return;
            }
            AddChar('.');
        }
    }

    void UpdateInputInView(const std::string& string) {
        if (!view_) {
            return;
        }
        view_->SetInputText(string);
        text_ = string;
    }

    void SetErrorInView(const std::string& string) {
        if (!view_) {
            return;
        }
        view_->SetErrorText(string);
    }

    void SetFormulaInView(const std::string& string) {
        if (!view_) {
            return;
        }
        view_->SetFormulaText(string);
        formula_ = string;
    }

    void SetMemInView(const std::string& string) {
        if (!view_) {
            return;
        }
        view_->SetMemText(string);
        mem_text_ = string;
    }

    void RevealView() {
        if (!view_) {
            return;
        }
        view_->SetInputText(text_);
        view_->SetFormulaText(formula_);
        view_->SetMemText(mem_text_);
        view_->SetExtraKey(GetExtraKey());
    }

private:
    std::function<std::optional<Error>(Number number)> operation_;
    std::string operation_name_;

    Calculator<Number> calculator_;

    Number active_number_ = {};
    std::string input_;

    MainWindow* view_ = nullptr;

    std::optional<Number> mem_ = {};

    bool input_as_number_ = true;

    std::string text_;
    std::string formula_;
    std::string mem_text_;
};