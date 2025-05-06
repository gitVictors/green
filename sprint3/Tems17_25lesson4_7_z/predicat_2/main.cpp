#include <algorithm>
#include <iostream>
#include <cassert>

#include "train.h"

int CountCompartment(const std::vector<Compartment>& compartments, Place is_empty, Gender gender) {
    // Ваше решение.
    // Создайте предикат и используйте его в алгоритме.
    // Параметр is_empty принимает значение — купе пустое или полностью заполненное.
    // Параметр gender — ограничение купе по гендерному признаку (женское, мужское и без ограничений).
    auto cnt_com = [=](Compartment cmpt) {
        if (gender == cmpt.gender){
            if (cmpt.lower_left == is_empty &&
                cmpt.lower_right == is_empty &&
                cmpt.upper_left == is_empty &&
                cmpt.upper_right == is_empty
                )
                return true;
            else
                return false;
        }
        return false;
    };

    auto cn = std::count_if (compartments.begin(), compartments.end(), cnt_com );

    return cn;
}

bool HasFreeCompartment(const std::vector<Compartment>& compartments, Gender gender) {
    // Ваше решение.
    // Создайте предикат и используйте его в алгоритме.
    // возвращает истину при наличии в поезде хоть одного полностью свободного купе в зависимости от запроса
    // по гендерному признаку (женское, мужское и без ограничений).

    auto fnd_gnd = [=](Compartment cmpt ) {
        if (cmpt.gender == gender){
            if(cmpt.lower_left == Place::FREE &&
                cmpt.lower_right == Place::FREE &&
                cmpt.upper_left == Place::FREE &&
                cmpt.upper_right == Place::FREE
                ) return true;
            else
                return  false;
        }else
            return false;
    };

    auto res = std::find_if (compartments.begin(), compartments.end(), fnd_gnd);

    if ( res != compartments.end())
        return true;
    else
        return false;
}

FreeCompartment HasFreeCompartme(const std::vector<Compartment>& compartments) {
    // Ваше решение.
    // Напишите функцию, которая вернёт информацию есть ли свободные купе.
    // Возврат информации по наличию свободных купе для мужчин, женщин и без требования по гендерному признаку

    FreeCompartment res;

    res.has_free_compartment_for_all = HasFreeCompartment( compartments, Gender::NOT_SPECIFIED );
    res.has_free_compartment_for_men = HasFreeCompartment( compartments, Gender::MALE);
    res.has_free_compartment_for_women = HasFreeCompartment ( compartments, Gender::FEMALE );

    return res;
}

CompartmentInfo GetCompartmentStat(const std::vector<Compartment>& compartments) {
    // Ваше решение.
    // Напишите функцию, которая соберёт статистику по вагонам.
    // Возврат посчитанных свободных/занятых купе при разных значениях по гендерному признаку
    // принимает на вход вектор купе и возвращает данные в структурированном виде:

    CompartmentInfo res;

    res.empty_for_all = CountCompartment (compartments, Place::FREE ,  Gender::NOT_SPECIFIED);
    res.empty_for_men = CountCompartment(compartments, Place::FREE, Gender::MALE);
    res.empty_for_women = CountCompartment(compartments, Place::FREE, Gender::FEMALE);

    res.full_for_all = CountCompartment(compartments, Place::NOT_FREE, Gender::NOT_SPECIFIED);
    res.full_for_men = CountCompartment(compartments, Place::NOT_FREE, Gender::MALE);
    res.full_for_women = CountCompartment(compartments, Place::NOT_FREE, Gender::FEMALE);

    return res;
}

int main() {
    Compartment free_men = {
                            .gender = Gender::MALE,
                            .lower_left = Place::FREE, .lower_right = Place::FREE,
                            .upper_left = Place::FREE, .upper_right = Place::FREE};
    Compartment free_women = {
                              .gender = Gender::FEMALE,
                              .lower_left = Place::FREE, .lower_right = Place::FREE,
                              .upper_left = Place::FREE, .upper_right = Place::FREE};
    Compartment free_not_spec = {
                                 .gender = Gender::NOT_SPECIFIED,
                                 .lower_left = Place::FREE, .lower_right = Place::FREE,
                                 .upper_left = Place::FREE, .upper_right = Place::FREE};
    Compartment full_men = {
                            .gender = Gender::MALE,
                            .lower_left = Place::NOT_FREE, .lower_right = Place::NOT_FREE,
                            .upper_left = Place::NOT_FREE, .upper_right = Place::NOT_FREE};
    Compartment full_women = {
                              .gender = Gender::FEMALE,
                              .lower_left = Place::NOT_FREE, .lower_right = Place::NOT_FREE,
                              .upper_left = Place::NOT_FREE, .upper_right = Place::NOT_FREE};
    Compartment full_not_spec = {
                                 .gender = Gender::NOT_SPECIFIED,
                                 .lower_left = Place::NOT_FREE, .lower_right = Place::NOT_FREE,
                                 .upper_left = Place::NOT_FREE, .upper_right = Place::NOT_FREE};
    Compartment half_men = {
                            .gender = Gender::MALE,
                            .lower_left = Place::FREE, .lower_right = Place::NOT_FREE,
                            .upper_left = Place::FREE, .upper_right = Place::NOT_FREE};
    Compartment half_women = {
                              .gender = Gender::FEMALE,
                              .lower_left = Place::FREE, .lower_right = Place::NOT_FREE,
                              .upper_left = Place::FREE, .upper_right = Place::NOT_FREE};
    Compartment half_not_spec = {
                                 .gender = Gender::NOT_SPECIFIED,
                                 .lower_left = Place::FREE, .lower_right = Place::NOT_FREE,
                                 .upper_left = Place::FREE, .upper_right = Place::NOT_FREE};

    {
        std::vector<Compartment> compartments = {
            free_men
        };

        auto info = GetCompartmentStat(compartments);
        assert(info.empty_for_all == 0
               && info.empty_for_men == 1
               && info.empty_for_women == 0
               && info.full_for_all == 0
               && info.full_for_men == 0
               && info.full_for_women == 0);

    }

    {
        std::vector<Compartment> compartments = {
            free_men, free_men, free_women
        };
        auto info = GetCompartmentStat(compartments);
        assert(info.empty_for_all == 0
               && info.empty_for_men == 2
               && info.empty_for_women == 1
               && info.full_for_all == 0
               && info.full_for_men == 0
               && info.full_for_women == 0);

    }

    {
        std::vector<Compartment> compartments = {
            free_women, free_women, free_not_spec
        };
        auto info = GetCompartmentStat(compartments);
        assert(info.empty_for_all == 1
               && info.empty_for_men == 0
               && info.empty_for_women == 2
               && info.full_for_all == 0
               && info.full_for_men == 0
               && info.full_for_women == 0);

    }

    {
        std::vector<Compartment> compartments = {
            full_men, full_women, full_not_spec, half_women
        };
        auto info = GetCompartmentStat(compartments);
        assert(info.empty_for_all == 0
               && info.empty_for_men == 0
               && info.empty_for_women == 0
               && info.full_for_all == 1
               && info.full_for_men == 1
               && info.full_for_women == 1);

    }

    {
        // Полузаполненные купе не считаем.
        std::vector<Compartment> compartments = {
            half_men, full_women, half_not_spec
        };
        auto info = GetCompartmentStat(compartments);
        assert(info.empty_for_all == 0
               && info.empty_for_men == 0
               && info.empty_for_women == 0
               && info.full_for_all == 0
               && info.full_for_men == 0
               && info.full_for_women == 1);

    }
    std::cout << "ok" << std::endl;
}


// if ( pos == compartments.end() )
// {
//     res.has_free_compartment_for_all =false;
//     res.has_free_compartment_for_men =false;
//     res.has_free_compartment_for_women = false;
// } else {
//     if (pos.gender == Gender::MALE )
//         res.has_free_compartment_for_men = true;
//     else if (pos.gender ==  Gender::FEMALE)
//         res.has_free_compartment_for_women = true;
//     else
//         res.has_free_compartment_for_all = true;
// }
