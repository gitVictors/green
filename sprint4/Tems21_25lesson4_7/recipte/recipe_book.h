#pragma once

#include <map>
#include <string>
#include <vector>
#include <optional>

class RecipeBook {
public:

     RecipeBook() = default;

    // Конструктор с параметром для инициализации списка рецептов
    explicit RecipeBook(const std::map<std::string, std::map<std::string, int>>& initialRecipes)
        : recipes_(initialRecipes) {}

    // Метод для добавления нового рецепта
    bool AddRecipe(const std::string& recipeName, const std::map<std::string, int>& ingredients) {
        if (recipes_.find(recipeName) != recipes_.end()) {
            return false;  // Рецепт уже существует
        }
        recipes_[recipeName] = ingredients;
        return true;
    }

    // Метод для удаления рецепта
    bool DropRecipe(const std::string& recipeName) {
        auto it = recipes_.find(recipeName);
        if (it == recipes_.end()) {
            return false;  // Рецепт не найден
        }
        recipes_.erase(it);
        return true;
    }

    // Метод для получения всех названий рецептов
    std::vector<std::string> GetAllRecipes() const {
        std::vector<std::string> recipeNames;
        for (const auto& [recipeName, ingredients] : recipes_) {
            recipeNames.push_back(recipeName);
        }
        return recipeNames;
    }

    // Метод для получения рецепта по названию
    std::optional<std::map<std::string, int>> GetRecipe(const std::string& recipeName) const {
        auto it = recipes_.find(recipeName);
        if (it == recipes_.end()) {
            return std::nullopt;
        }
        return it->second;
    }

    // Метод для поиска рецептов по ингредиенту
    std::vector<std::string> FindByIngredient(const std::string& ingredient) const {
        std::vector<std::string> matchingRecipes;
        for (const auto& [recipeName, ingredients] : recipes_) {
            if (ingredients.find(ingredient) != ingredients.end()) {
                matchingRecipes.push_back(recipeName);
            }
        }
        return matchingRecipes;
    }

private:
    std::map<std::string, std::map<std::string, int>> recipes_;
};
