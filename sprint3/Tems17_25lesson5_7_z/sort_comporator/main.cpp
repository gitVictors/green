#include "student.h"

#include <algorithm>
#include <iostream>
#include <optional>
#include <vector>

template<typename Comparator>
void PrintTop(std::vector<Student> all_students,
              std::optional<int> max_top,
              Comparator comparator) {
    // Напишите здесь код.
    std::stable_sort(all_students.begin(), all_students.end(), comparator);

    size_t count = all_students.size();
    if (max_top.has_value() && max_top.value() < count) {
        count = static_cast<size_t>(max_top.value());
    }

    for (int i = 0; i < count; ++i) {
        std::cout << all_students[i] << std::endl;
    }

}

//сравнение по фамилиям по алфавиту (от А до Я) с именованием;
bool CompareSurnameAsc(const Student& s1, const Student& s2) {

    if (s1.last_name < s2.last_name)
        return true;

    return false;

}

// сравнение в обратном направлении (от Я до А);
bool CompareSurnameDesc(const Student& s1, const Student& s2) {

    if ( s1.last_name > s2.last_name )
        return true;

    return false;
}

// сравнение по среднему баллу по убыванию;
bool CompareMeanScoreDesc(const Student& s1, const Student& s2) {

    return s1.mean_score > s2.mean_score;
}

// сравнение по количеству пятёрок в оценках по убыванию;
bool CompareBestScoreDesc(const Student& s1, const Student& s2) {

    auto cnt1 = std::count(s1.all_scores.begin(), s1.all_scores.end(), 5);
    auto cnt2 = std::count(s2.all_scores.begin(), s2.all_scores.end(), 5);

    return cnt1 > cnt2;
}

 // сравнение по количеству пятёрок, а в случае равенства количества пятёрок — по среднему баллу.
bool LexicographicalScoreCompare(const Student& s1, const Student& s2) {

    size_t count1 = std::count(s1.all_scores.begin(), s1.all_scores.end(), 5);
    size_t count2 = std::count(s2.all_scores.begin(), s2.all_scores.end(), 5);

    if (count1 != count2) {
        return count1 > count2; // больше пятёрок — выше в списке
    }
    return s1.mean_score > s2.mean_score; // при равенстве — выше средний балл

}

int main() {
    std::vector<Student> students;
    Student student;
    while(std::cin >> student) {
        students.push_back(student);
    }
    std::cout << "- Топ студентов с компаратором CompareSurnameAsc"
              << std::endl;
    PrintTop(students, std::nullopt, CompareSurnameAsc);

    std::cout << "- Топ-10 студентов с компаратором CompareSurnameDesc"
              << std::endl;
    PrintTop(students, 10, CompareSurnameDesc);

    std::cout << "- Топ-4 студентов с компаратором CompareMeanScoreDesc"
              << std::endl;
    PrintTop(students, 4, CompareMeanScoreDesc);

    std::cout << "- Топ-3 студентов с компаратором LexicographicalScoreCompare"
              << std::endl;
    PrintTop(students, 3, LexicographicalScoreCompare);
}
