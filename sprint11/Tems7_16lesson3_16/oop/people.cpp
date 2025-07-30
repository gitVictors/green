#include "people.h"

#include <stdexcept>
#include <algorithm>

using namespace std;

Programmer::Programmer(const string& name, int age, Gender gender):
    Person(name, age, gender)
{
    // Напишите тело конструктора
}


void Programmer::AddProgrammingLanguage(ProgrammingLanguage language) {

    programmingLanguage_.push_back(language);

}

bool Programmer::CanProgram(ProgrammingLanguage language) const {


    auto it = std::find(programmingLanguage_.begin(), programmingLanguage_.end(), language);

    if (it == programmingLanguage_.end())
        return false;
    else
        return true;
}

Worker::Worker(const string& name, int age, Gender gender):
    Person(name, age, gender)
{
}


void Worker::AddSpeciality(WorkerSpeciality speciality) {
    worker_speciality_.push_back(speciality);
}

bool Worker::HasSpeciality(WorkerSpeciality speciality) const {

    auto it = std::find(worker_speciality_.begin(), worker_speciality_.end(), speciality);

    if (it == worker_speciality_.end()) {
        return false;
    }
    else {
        return true;
    }

}


//Person
const std::string& Person::GetName() const{
    if (name_.empty()){
         throw std::logic_error("Not implemented"s);
    }
    return name_;
}

int Person::GetAge() const{
    return age_;
}

Gender Person::GetGender() const{
    return gender_;
}
