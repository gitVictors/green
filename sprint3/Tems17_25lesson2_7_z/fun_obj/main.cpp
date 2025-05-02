#include "coffeebar.h"
#include <cassert>

int DoRecipe(const std::vector<RecipeAction>& recipe, Cup& cup) {
    int total_time = 0;

    for (const auto& action: recipe) {
        total_time += action(cup);
    }

    return total_time;
}

int AddCoffee(Cup& cup) {
    cup.coffee += 50;
    return 15;
}

int AddWater(Cup& cup) {
    cup.water += 50;
    return 15;
}

int AddMilk(Cup& cup) {
    cup.milk += 50;
    return 10;
}

int AddSteamedMilk(Cup& cup) {
    cup.steamed_milk += 50;
    return 20;
}

int AddCocoaPowder(Cup& cup) {
    cup.cocoa += 2;
    return 15;
}

int AddTeabag(Cup& cup) {
    cup.teabag += 1;
    return 3;
}

std::vector<RecipeAction> CreateRecipe(DrinkType drink_type) {

     std::vector<RecipeAction> recipe;

    switch (drink_type){
     case DrinkType::Americano :
        recipe.push_back(AddCoffee);
        recipe.push_back(AddWater);
        recipe.push_back(AddWater);
        break;
     case DrinkType::Latte :
         recipe.push_back(AddCoffee);
         recipe.push_back(AddMilk);
         recipe.push_back(AddMilk);
         recipe.push_back(AddSteamedMilk);
         break;
     case DrinkType::Cappuccino:
         recipe.push_back(AddCoffee);
         recipe.push_back(AddMilk);
         recipe.push_back(AddSteamedMilk);
         break;
     case DrinkType::Cocoa :
         recipe.push_back(AddCocoaPowder);
         recipe.push_back(AddMilk);
         recipe.push_back(AddMilk);
         recipe.push_back(AddMilk);
         recipe.push_back(AddMilk);
         break;
     case DrinkType::Tea :
         recipe.push_back(AddTeabag);
         recipe.push_back(AddWater);
         recipe.push_back(AddWater);
         recipe.push_back(AddWater);
         recipe.push_back(AddWater);
         break;
     default:
         break;
    }

    return recipe;
}

int main() {
    {
        auto recipe = CreateRecipe(DrinkType::Americano);
        Cup cup;

        int time = DoRecipe(recipe, cup);
        assert(time == 45);
        assert((cup == Cup{
                    .coffee = 50,
                    .water = 100
                }));
    }
    {
        auto recipe = CreateRecipe(DrinkType::Cocoa);
        Cup cup;

        int time = DoRecipe(recipe, cup);
        assert(time == 55);
        assert((cup == Cup{
                    .cocoa = 2,
                    .milk = 200
                }));
    }
}
