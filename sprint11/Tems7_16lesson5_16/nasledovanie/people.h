#pragma once

#include <string>

class Person;

// Наблюдатель за состоянием человека.
class PersonObserver {
public:
    // Этот метод вызывается, когда меняется состояние удовлетворённости человека
    virtual void OnSatisfactionChanged(Person& /*person*/, int /*old_value*/, int /*new_value*/) {
        // Реализация метода базового класса ничего не делает
    }

protected:
    // Класс PersonObserver не предназначен для удаления напрямую
    ~PersonObserver() = default;
};

/*
    Человек.
    При изменении уровня удовлетворённости уведомляет
    связанного с ним наблюдателя
*/
class Person {
public:
    Person(const std::string& name, int age)
        : dance_(0), name_(name), age_(age), satisfaction_(100), observer_(nullptr)
    {
        // Напишите реализацию самостоятельно
    }
    virtual ~Person() = default;

    int GetSatisfaction() const {
        return satisfaction_;
    }

    const std::string& GetName() const {
        return name_;
    }


    // «Привязывает» наблюдателя к человеку. Привязанный наблюдатель
    // уведомляется об изменении уровня удовлетворённости человека
    // Новый наблюдатель заменяет собой ранее привязанного
    // Если передать nullptr в качестве наблюдателя, это эквивалентно отсутствию наблюдателя
    void SetObserver(PersonObserver* observer) {
        // Напишите реализацию самостоятельно
        observer_ = observer;
    }


    int GetAge() const {
        return age_;
    }

    // Увеличивает на 1 количество походов на танцы
    // Увеличивает удовлетворённость на 1
    virtual void Dance() {
        dance_ ++;
        int old_satisfaction = satisfaction_;
        satisfaction_++;
        if (observer_) {
            observer_->OnSatisfactionChanged(*this, old_satisfaction, satisfaction_);
        }
    }

    int GetDanceCount() const {
        // Заглушка. Напишите реализацию самостоятельно
        return dance_;
    }

    // Прожить день. Реализация в базовом классе ничего не делает
    virtual void LiveADay() {
        // Подклассы могут переопределить этот метод
    }

protected:
    void SetSatisfaction(int value) {
        if (satisfaction_ != value) {
            int old_satisfaction = satisfaction_;
            satisfaction_ = value;
            // Если у человека есть наблюдатель, сообщаем ему об изменении удовлетворённости
            if (observer_) {
                observer_->OnSatisfactionChanged(*this, old_satisfaction, satisfaction_);
            }
        }
    }

protected:
      int dance_;

private:
    std::string name_;
    int age_;
    int satisfaction_ = 100;

    PersonObserver* observer_ = nullptr;
};

// Рабочий.
// День рабочего проходит за работой
class Worker : public Person {
public:
    Worker(const std::string& name, int age):Person(name, age), work_count_(0)
    {
        // Напишите недостающий код
    }

    // Рабочий старше 30 лет и младше 40 за танец получает 2 единицы удовлетворённости вместо 1

    void Dance() override {
        dance_++; // Увеличиваем счетчик танцев
        if (GetAge() > 30 && GetAge() < 40) {
            SetSatisfaction(GetSatisfaction() + 2); // +2 для рабочих 30-40 лет
        } else {
            SetSatisfaction(GetSatisfaction() + 1); // +1 для остальных
        }
    }

    // День рабочего проходит за работой
    void LiveADay() override{
        Work();
    }

    // Увеличивает счётчик сделанной работы на 1, уменьшает удовлетворённость на 5
    void Work() {
        work_count_++;
        SetSatisfaction(GetSatisfaction() - 5);
    }

    // Возвращает значение счётчика сделанной работы
    int GetWorkDone() const {
        // Заглушка. Напишите реализацию самостоятельно
        return work_count_;
    }
private:
    int work_count_=0;

};

// Студент.
// День студента проходит за учёбой
class Student :  public Person {
public:
    Student(const std::string& name, int age): Person(name, age), knowledge_level_(0)
    {
        // Напишите недостающий код
    }

    // День студента проходит за учёбой
    void LiveADay() override{
       Study();
    }
    // Учёба увеличивает уровень знаний на 1, уменьшает уровень удовлетворённости на 3
    void Study() {
        knowledge_level_++;
        SetSatisfaction(GetSatisfaction() - 3);
    }

    // Возвращает уровень знаний
    int GetKnowledgeLevel() const {
        // Заглушка, напишите реализацию самостоятельно
       return knowledge_level_;
    }

private:
int knowledge_level_;


};
