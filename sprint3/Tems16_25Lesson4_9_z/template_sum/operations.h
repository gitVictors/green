#pragma once

#include <string>

enum class OperationType {
    OP_SUM,
    OP_PROD,
    OP_MAX,
};

// Сумма параметров.
template<typename T, typename S, typename U>
T Sum(T t, S s, U u){
    return t + s + u;
}

// Произведение параметров.
template<typename T, typename S, typename U>
T Prod(T t, S s, U u){
    return t * s * u;
}

// Определение максимума.
template<typename T, typename S, typename U>
T Max(T t, S s, U u){

    // Сравниваем первый и второй аргумент, находим максимум
    auto max_temp = t > s ? t : s;

    // Сравниваем временный максимум с третьим аргументом
    return max_temp > u ? max_temp : u;

}

// Вызов указанной функции для параметров t, s, u.
template<typename T, typename S, typename U>
T DoOperation(T t, S s, U u, OperationType operation){

    T res{0};

    if (operation == OperationType::OP_SUM)
        return Sum(t, s, u);

    if (operation == OperationType::OP_PROD)
        return Prod(t, s, u);

    if (operation == OperationType::OP_MAX)
        return Max(t,s,u);

    return res;
}

//  Cпециализация Prod для строк.
template<>
std::string Prod(std::string t, std::string s, std::string u) {
    using namespace std::literals;
    return t + " * "s + s + " * "s + u;
}
