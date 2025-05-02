#pragma once

template <typename T>
class Optional {
public:
    // Напишите следующие методы.
    Optional() = default;
    Optional(const T& value): has_value_(true) ,  value_(value) {}

    // Возвращает true, если класс содержит значение.
    bool HasValue() const{
        if (has_value_ == true)
            return true;
        else
            return false;
    }

    // Возвращает значение.
    T GetValue() const{
        return value_;
    }

    // Устанавливает новое значение.
    void SetValue(T value){
        has_value_ = true;
        value_ = value;
    }

    // Удаляет значение.
    void Reset(){
        has_value_ = false;
    }

private:
    bool has_value_ = false;
    T value_{};
};
