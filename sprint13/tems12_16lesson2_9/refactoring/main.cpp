#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Gender { FEMALE, MALE };

struct Person {
    int age;           // возраст
    Gender gender;     // пол
    bool is_employed;  // имеет ли работу
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
    if (range_begin == range_end) {
        return 0;
    }
    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = range_copy.begin() + range_copy.size() / 2;
    nth_element(range_copy.begin(), middle, range_copy.end(), [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
    });
    return middle->age;
}

// напишите сигнатуру и реализацию функции PrintStats
void PrintStats(vector<Person> person) {

    int median_age =  ComputeMedianAge(person.begin() , person.end());
    cout << "Median age = "s << median_age << endl;

    //============
    auto it = std::partition (person.begin(), person.end(), [median_age](const Person& person){
        return person.gender == Gender::FEMALE;
    } ) ;
    median_age = ComputeMedianAge(person.begin(), it);
    cout << "Median age for females = "s << median_age << endl;

    //============
    it = std::partition(person.begin(), person.end(), [](const Person& person){
        return person.gender == Gender::MALE;
    });
    median_age = ComputeMedianAge(person.begin(), it);
    cout << "Median age for males = "s << median_age << endl;

    //============
    it = std::partition(person.begin(), person.end(), [](const Person& person){
        return (person.gender == Gender::FEMALE && person.is_employed == true);
    });
    median_age = ComputeMedianAge(person.begin(), it);
    cout << "Median age for employed females = "s << median_age << endl;

    //============
    it = std::partition(person.begin(), person.end(), [](const Person& person){
        return (person.gender == Gender::FEMALE && person.is_employed == false);
    });
    median_age = ComputeMedianAge(person.begin(), it);
    cout << "Median age for unemployed females = "s << median_age << endl;

    //====
    it = std::partition(person.begin(), person.end(), [](const Person& person){
        return (person.gender == Gender::MALE && person.is_employed == true);
    });
    median_age = ComputeMedianAge(person.begin(), it);
    cout << "Median age for employed males = " << median_age << endl;


    //====
    it = std::partition(person.begin(), person.end(), [](const Person& person){
        return (person.gender == Gender::MALE && person.is_employed == false);
    });
    median_age = ComputeMedianAge(person.begin(), it);
    cout << "Median age for unemployed males = "s << median_age << endl;

    return;
}

int main() {
    vector<Person> persons = {
                              {31, Gender::MALE, false},   {40, Gender::FEMALE, true},  {24, Gender::MALE, true},
                              {20, Gender::FEMALE, true},  {80, Gender::FEMALE, false}, {78, Gender::MALE, false},
                              {10, Gender::FEMALE, false}, {55, Gender::MALE, true},
                              };
    PrintStats(persons);
}
