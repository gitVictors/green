#include <cassert>
#include <string>
#include "recipe_book.h"


int main() {
    using namespace std::literals;
    {
        RecipeBook recipeBook;
        assert(recipeBook.GetAllRecipes().size() == 0);

        assert(recipeBook.AddRecipe("Cake"s, {{"sugar"s, 50}, {"flour"s, 100}}));
        assert(recipeBook.GetAllRecipes().size() == 1);

        assert(!recipeBook.AddRecipe("Cake"s, {{"cake mix"s, 220}}));
        assert(recipeBook.GetAllRecipes().size() == 1);

        assert(recipeBook.AddRecipe("Pasta"s, {{"pasta"s, 200}, {"tomato"s, 1}}));
        assert(recipeBook.AddRecipe("Salad"s, {{"lettuce"s, 200}, {"tomato"s, 2}}));
        assert(recipeBook.GetAllRecipes().size() == 3);
    } {
        std::map<std::string, std::map<std::string, int>> initialRecipes = {
            {"Pasta"s, {{"pasta"s, 200}, {"tomato"s, 1}}},
            {"Salad"s, {{"lettuce"s, 100}, {"tomato"s, 2}}}
        };
        RecipeBook recipeBook(initialRecipes);
        assert(recipeBook.GetAllRecipes().size() == 2);
        assert(recipeBook.GetAllRecipes().at(0) == "Pasta"s);
        assert(recipeBook.GetAllRecipes().at(1) == "Salad"s);
    } {
        std::map<std::string, std::map<std::string, int>> initialRecipes = {
            {"Pasta"s, {{"pasta"s, 200}, {"tomato"s, 1}}},
            {"Salad"s, {{"lettuce"s, 100}, {"tomato"s, 2}}}
        };
        RecipeBook recipeBook(initialRecipes);
        assert(recipeBook.GetAllRecipes().size() == 2);

        assert(!recipeBook.DropRecipe("Cake"s));
        assert(recipeBook.GetAllRecipes().size() == 2);

        assert(recipeBook.DropRecipe("Pasta"s));
        assert(recipeBook.GetAllRecipes().size() == 1);

        assert(!recipeBook.DropRecipe("Pasta"s));
        assert(recipeBook.GetAllRecipes().size() == 1);

        assert(recipeBook.DropRecipe("Salad"s));
        assert(recipeBook.GetAllRecipes().size() == 0);
    } {
        std::map<std::string, std::map<std::string, int>> initialRecipes = {
            {"Pasta"s, {{"pasta"s, 200}, {"tomato"s, 1}}},
            {"Salad"s, {{"lettuce"s, 100}, {"tomato"s, 2}}}
        };
        RecipeBook recipeBook(initialRecipes);

        assert(!recipeBook.GetRecipe("Cake"s).has_value());
        assert(recipeBook.GetRecipe("Salad"s).has_value());
        assert(recipeBook.GetRecipe("Salad"s).value() == initialRecipes.at("Salad"s));

        std::map<std::string, int> initialCake = {
            {"sugar"s, 50},
            {"flour"s, 100}
        };
        recipeBook.AddRecipe("Cake"s, initialCake);
        assert(recipeBook.GetRecipe("Cake"s).has_value());
        assert(recipeBook.GetRecipe("Cake"s).value() == initialCake);

        assert(recipeBook.DropRecipe("Cake"s));
        assert(!recipeBook.GetRecipe("Cake"s).has_value());

    } {
        std::map<std::string, std::map<std::string, int>> initialRecipes = {
            {"Pasta"s, {{"pasta"s, 200}, {"tomato"s, 1}}},
            {"Salad"s, {{"lettuce"s, 100}, {"tomato"s, 2}}},
            {"Soup"s, {{"carrot"s, 2}, {"onion"s, 1}}}
        };
        RecipeBook recipeBook(initialRecipes);

        assert(recipeBook.FindByIngredient("tomato"s).size() == 2);
        assert(recipeBook.FindByIngredient("tomato"s).at(0) == "Pasta"s);
        assert(recipeBook.FindByIngredient("tomato"s).at(1) == "Salad"s);

        assert(recipeBook.FindByIngredient("lettuce"s).size() == 1);
        assert(recipeBook.FindByIngredient("lettuce"s).at(0) == "Salad"s);

        assert(recipeBook.FindByIngredient("sugar"s).size() == 0);
    }
}
