#pragma once
#include <stdexcept>

class Led {
public:
    bool GetState() const {
        return state_;
    }
    void SetState(bool state) {
        // Ваша реализация метода.
        state_ =  state;
    }
private:
    bool state_ = false;
};

class Switch {
public:
    Switch() {
            // Реализация конструктора без параметров.
        led_ptr_ = nullptr;
    }

/*указатель на объект Led */
    Switch(Led* ld)  {
                // Реализация конструктора, принимающего указатель.
        led_ptr_ = ld;
    }

    void ChangeState() {
        // Ваша реализация метода.
        if (led_ptr_ == nullptr)
            throw std::invalid_argument ("Указатель пустой");
        bool val  = !led_ptr_->GetState();
        led_ptr_->SetState( val );

    }
    /*указатель на объект Led */
    void ChangeLed(Led* ld) {
            // Ваша реализация метода.
            led_ptr_ = ld;
    }
private:
    // Создайте необходимые поля класса.
    Led* led_ptr_;
};