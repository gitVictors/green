#include "led.h"

#include <cassert>

void Test1() {
    // Создание одной лампочки с двумя переключателями.
    Led led;
    Switch led_switch_1{&led};
    Switch led_switch_2{&led};

    led_switch_1.ChangeState();
    assert(led.GetState());
    led_switch_2.ChangeState();
    assert(!led.GetState());
}

void Test2() {
    // Создание пустого выключателя.
    Switch empty_switch;
    bool was_exception = false;
    try {
        empty_switch.ChangeState();
    } catch(const std::invalid_argument& ie) {
        was_exception = true;
    }
    assert(was_exception);

    Led led;
    empty_switch.ChangeLed(&led);

    assert(!led.GetState());
    empty_switch.ChangeState();
    assert(led.GetState());
}

void Test3() {
    // Создание двух пар лапмочка-переключатель.
    Led led1;
    Switch led_switch_1{&led1};

    Led led2;
    Switch led_switch_2{&led2};

    led_switch_1.ChangeState();
    assert(led1.GetState());
    assert(!led2.GetState());
    led_switch_2.ChangeState();
    assert(led1.GetState());
    assert(led2.GetState());
}

int main() {
    Test1();
    Test2();
    Test3();
}