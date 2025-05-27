#pragma once

#include <set>
#include <string>

class AutocompleteEngine {
private:
    using Storage = std::set<std::string>;

public:
    using It = Storage::const_iterator;

public:
    AutocompleteEngine() {
    }

    // Следующие два метода нужно реализовать.
    void AddName(const std::string& name) {

        if( name.empty())
            return;

        names_.insert(name);
    }

    std::pair<It, It> Autocomplete(const std::string& input, size_t max_names) const {

        if (names_.empty()) {
            return {names_.end(), names_.end()};
        }

        // Начало диапазона: первое имя >= input
        auto lower = names_.lower_bound(input);

        // Проверяем, что имя действительно начинается с input
        if (lower == names_.end() || lower->find(input) != 0) {
            return {names_.end(), names_.end()};
        }

        // Конец диапазона: первое имя > input + '\xFF'
        std::string upper_bound_str = input + '\xFF';
        auto upper = names_.upper_bound(upper_bound_str);

        // Ограничиваем количество результатов
        if (max_names > 0) {
            auto distance = std::distance(lower, upper);
            if (distance > static_cast<decltype(distance)>(max_names)) {
                upper = lower;
                std::advance(upper, max_names);
            }
        }

        return {lower, upper};
    }

private:
    // Тут должен быть Storage, в котором будут храниться имена.
    Storage names_;
};
