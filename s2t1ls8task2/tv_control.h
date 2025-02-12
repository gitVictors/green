#pragma once

#include <string>

#include "tv.h"

class TVControl {
public:
    // Считывает из стандартного потока ввода команду управления телевизором
    // и выполняет эту команду, используя телевизор tv.
    // Возвращает true в случае успеха.
    // Возвращает false, если произошла ошибка разбора команды или была введена команда Exit.
    static bool ReadAndApplyCommand(TV& tv);

private:
    static void Info(TV& tv);
};