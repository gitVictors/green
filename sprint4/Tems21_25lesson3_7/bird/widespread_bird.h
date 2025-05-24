#pragma once

#include <vector>
#include <string>
#include <map>
#include <algorithm>

// Допишите функцию FindWidespreadBird.
// inline std::string FindWidespreadBird( ... )


inline std::string FindWidespreadBird(const std::vector<std::string>& birds) {
    std::map<std::string, int> bird_counts;

    // Подсчитываем количество вхождений каждой птицы
    for (const auto& bird : birds) {
        bird_counts[bird]++;
    }

    std::string widespread_bird;
    int max_count = 0;

    // Находим птицу с максимальным количеством вхождений
    for (const auto& [bird, count] : bird_counts) {
        if (count > max_count) {
            max_count = count;
            widespread_bird = bird;
        } else if (count == max_count && bird < widespread_bird) {
            // Если количество одинаковое, выбираем первую по алфавиту
            widespread_bird = bird;
        }
    }

    return widespread_bird;
}
