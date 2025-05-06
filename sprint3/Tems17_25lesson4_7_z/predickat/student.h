#pragma once

#include <vector>
#include <string>

struct Student {
    double mean_score;
    std::string first_name;
    std::string last_name;
    std::vector<int> all_scores;
};

// Следующие две функции реализуйте в cpp-файле.
bool HasBadGrade(const Student& student);
std::vector<Student> FilterBadGrades(std::vector<Student> students);
