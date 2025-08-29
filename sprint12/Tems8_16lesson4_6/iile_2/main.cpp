#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

struct Person {
    string name;
    int age, income;
    bool is_male;
};

vector<Person> ReadPeople(istream& input) {
    int count;
    input >> count;

    vector<Person> result(count);
    for (Person& p : result) {
        char gender;
        input >> p.name >> p.age >> p.income >> gender;
        p.is_male = gender == 'M';
    }

    return result;
}

int main() {
    vector<Person> people = ReadPeople(cin);

    // Предподсчет для AGE: сортируем по возрасту
    vector<int> ages;
    ages.reserve(people.size());
    for (const auto& p : people) {
        ages.push_back(p.age);
    }
    sort(ages.begin(), ages.end());

    // Предподсчет для WEALTHY: сортируем по доходу и считаем префиксные суммы
    vector<int> incomes;
    incomes.reserve(people.size());
    for (const auto& p : people) {
        incomes.push_back(p.income);
    }
    sort(incomes.begin(), incomes.end(), greater<int>());

    vector<int> prefix_sum(incomes.size());
    if (!incomes.empty()) {
        prefix_sum[0] = incomes[0];
        for (size_t i = 1; i < incomes.size(); ++i) {
            prefix_sum[i] = prefix_sum[i-1] + incomes[i];
        }
    }

    // Предподсчет для POPULAR_NAME: разделяем по полу и сортируем по имени
    vector<Person> males, females;
    for (const auto& p : people) {
        if (p.is_male) {
            males.push_back(p);
        } else {
            females.push_back(p);
        }
    }

    auto ComputePopularName = [](vector<Person>& people) -> string {
        if (people.empty()) {
            return "";
        }

    sort(people.begin(), people.end(), [](const Person& lhs, const Person& rhs) {
            return lhs.name < rhs.name;
        });

        string most_popular_name = people[0].name;
        int max_count = 1;
        int current_count = 1;

        for (size_t i = 1; i < people.size(); ++i) {
            if (people[i].name == people[i-1].name) {
                current_count++;
            } else {
                if (current_count > max_count) {
                    max_count = current_count;
                    most_popular_name = people[i-1].name;
                } else if (current_count == max_count && people[i-1].name < most_popular_name) {
                    most_popular_name = people[i-1].name;
                }
                current_count = 1;
            }
        }

        // Проверяем последнюю группу
        if (current_count > max_count) {
            most_popular_name = people.back().name;
        } else if (current_count == max_count && people.back().name < most_popular_name) {
            most_popular_name = people.back().name;
        }

        return most_popular_name;
    };

    string popular_male = ComputePopularName(males);
    string popular_female = ComputePopularName(females);

    for (string command; cin >> command;) {
        if (command == "AGE"s) {
            int adult_age;
            cin >> adult_age;

            // Бинарный поиск по предподсчитанному вектору возрастов
            auto adult_begin = lower_bound(ages.begin(), ages.end(), adult_age);
            cout << "There are "s << distance(adult_begin, ages.end())
                 << " adult people for maturity age "s << adult_age << '\n';

        } else if (command == "WEALTHY"s) {
            int count;
            cin >> count;
            count = min(count, static_cast<int>(prefix_sum.size()));

            int total_income = count > 0 ? prefix_sum[count-1] : 0;
            cout << "Top-"s << count << " people have total income "s << total_income << '\n';

        } else if (command == "POPULAR_NAME"s) {
            char gender;
            cin >> gender;

            if (gender == 'M') {
                if (popular_male.empty()) {
                    cout << "No people of gender "s << gender << '\n';
                } else {
                    cout << "Most popular name among people of gender "s << gender
                         << " is "s << popular_male << '\n';
                }
            } else {
                if (popular_female.empty()) {
                    cout << "No people of gender "s << gender << '\n';
                } else {
                    cout << "Most popular name among people of gender "s << gender
                         << " is "s << popular_female << '\n';
                }
            }
        }
    }
}
