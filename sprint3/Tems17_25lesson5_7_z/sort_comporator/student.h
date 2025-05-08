#pragma once

// В этом файле определена структура Student и
// операции ввода-вывода для неё.
// Вносить сюда изменения не требуется.

#include <string>
#include <vector>
#include <sstream>
#include <iostream>



struct Student {
    double mean_score;
    std::string first_name;
    std::string last_name;
    std::vector<int> all_scores;
};

// Далее идут операции ввода-вывода учеников.

inline std::ostream& operator<<(std::ostream& out, const Student& student) {
    out << student.first_name << " " << student.last_name;
    return out;
};

inline std::istream& operator>>(std::istream& in, Student& student) {
    std::string line;
    std::istringstream line_input;

    // Читаем имя и фамилию.
    std::getline(in, line);
    line_input.str(line);
    if (!(line_input >> student.first_name >> student.last_name)) {
        in.setstate(std::ios::failbit);
        return in;
    }

    // Читаем оценки.
    std::getline(in, line);
    line_input.str(line);
    student.all_scores.clear();
    int grade;
    int sum = 0;
    while (line_input >> grade) {
        sum += grade;
        student.all_scores.push_back(grade);
    }
    student.mean_score = static_cast<double>(sum) / static_cast<double>(student.all_scores.size());

    return in;
};
