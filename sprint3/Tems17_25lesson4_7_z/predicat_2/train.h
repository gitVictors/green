#pragma once

#include <vector>

enum class Gender {
    MALE, FEMALE, NOT_SPECIFIED
};

enum class Place {
    FREE,
    NOT_FREE
};

struct Compartment {
    Gender gender;
    Place lower_left = Place::FREE;
    Place lower_right = Place::FREE;
    Place upper_left = Place::FREE;
    Place upper_right = Place::FREE;
};

struct FreeCompartment {
    bool has_free_compartment_for_men;
    bool has_free_compartment_for_women;
    bool has_free_compartment_for_all;
};

struct CompartmentInfo {
    int empty_for_men;
    int empty_for_women;
    int empty_for_all;

    int full_for_men;
    int full_for_women;
    int full_for_all;
};

// Следующие четыре функции реализуйте в cpp-файле.
int CountCompartment(
    const std::vector<Compartment>& compartments,
    Place is_empty,
    Gender gender
    );

bool HasFreeCompartment(
    const std::vector<Compartment>& compartments, Gender gender);

FreeCompartment HasFreeCompartment(
    const std::vector<Compartment>& compartments);

CompartmentInfo GetCompartmentStat(
    const std::vector<Compartment>& compartments);
