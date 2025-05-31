#include "practicum_tests.h"

PRAC_TEST(TvStatus) { 
    TV tv; 
    PracCheck(!tv.IsTurnedOn(), "Проверка: телевизор выключен после инициализации"); 
    tv.TurnOn(); 
    PracCheck(tv.IsTurnedOn(), "Проверка: телевизор включён после включения"); 
    tv.TurnOff(); 
    PracCheck(!tv.IsTurnedOn(), "Проверка: телевизор выключен после выключения"); 
}

// Добавьте сюда свои тесты.