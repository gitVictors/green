#include "practicum_tests.h"
#include "tv.h"

PRAC_TEST(TvStatus) { 
    TV tv; 
    PracCheck(!tv.IsTurnedOn(), "Проверка: телевизор выключен после инициализации"); 
    tv.TurnOn(); 
    PracCheck(tv.IsTurnedOn(), "Проверка: телевизор включён после включения"); 
    tv.TurnOff(); 
    PracCheck(!tv.IsTurnedOn(), "Проверка: телевизор выключен после выключения"); 
}

// Добавьте сюда свои тесты.

PRAC_TEST(InitialState){
    TV tv;
    PracCheck(!tv.IsTurnedOn(),  "Телевизор должен быть выключен после создания");
    PracCheck(tv.GetCurrent() == 1, "Текущий канал должен быть 1 после создания");
    PracCheck(tv.GetMinChan() == 1,  "Минимальный канал должен быть 1" );
    PracCheck(tv.GetMaxChan() == 100 , "Максимальный канал должен быть 100" );
}

PRAC_TEST(SetValidChannel) {
    TV tv;
    tv.TurnOn();
    tv.SetChannel(50);
    PracCheck(tv.GetCurrent() == 50, "Канал должен измениться на 50");
    tv.SetChannel(1);
    PracCheck(tv.GetCurrent() == 1, "Канал должен измениться на 1");
    tv.SetChannel(100);
    PracCheck(tv.GetCurrent() == 100, "Канал должен измениться на 100");
}

PRAC_TEST(SetInvalidChannel) {
    TV tv;
    tv.TurnOn();
    tv.SetChannel(50); // Устанавливаем валидный канал для проверки
    PracCheck(tv.GetCurrent() == 50, "Канал должен быть 50 перед проверкой невалидных значений");

    // Попытка установить канал меньше минимального
    tv.SetChannel(0);
    PracCheck(tv.GetCurrent() == 50, "Канал не должен измениться при установке 0");

    // Попытка установить канал больше максимального
    tv.SetChannel(101);
    PracCheck(tv.GetCurrent() == 50, "Канал не должен измениться при установке 101");

    // Проверка выключенного телевизора
    tv.TurnOff();
    tv.SetChannel(10);
    PracCheck(tv.GetCurrent() == 50, "Канал не должен измениться при выключенном телевизоре");
}
