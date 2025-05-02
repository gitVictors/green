#pragma once
#include <vector>
#include <functional>

struct Cup {
    int coffee = 0;
    int cocoa = 0;
    int teabag = 0;
    int water = 0;
    int milk = 0;
    int steamed_milk = 0;

    // Операция сравнения.
    bool operator==(const Cup&) const = default;
};

    /* определите RecipeAction */;
using RecipeAction = std::function<int(Cup&)>;


enum class DrinkType {
    Latte,
    Americano,
    Cappuccino,
    Cocoa,
    Tea
};

int DoRecipe(const std::vector<RecipeAction>& recipe, Cup& cup);

std::vector<RecipeAction> CreateRecipe(DrinkType drink_type);
