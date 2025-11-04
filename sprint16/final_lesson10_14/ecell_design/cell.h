#pragma once

#include "common.h"
#include "formula.h"

#include <memory>
#include <string>
#include <unordered_set>

// Предварительное объявление для разрешения циклических зависимостей
class Sheet;

class Cell : public CellInterface {
public:
    Cell(Sheet& sheet);  // Добавлен параметр - ссылка на таблицу
    ~Cell();

    void Set(std::string text) override;
    void Clear();

    Value GetValue() const override;
    std::string GetText() const override;

    // Новые методы для управления зависимостями
    const std::unordered_set<Position, PositionHash>& GetReferencedCells() const;
    void AddDependent(Position pos);
    void RemoveDependent(Position pos);
    void InvalidateCache();
    bool IsCacheValid() const;

private:
    class Impl;
    class EmptyImpl;
    class TextImpl;
    class FormulaImpl;

    std::unique_ptr<Impl> impl_;
    Sheet& sheet_;  // Ссылка на таблицу для вычисления формул

    // Граф зависимостей
    std::unordered_set<Position, PositionHash> dependencies_;  // Ячейки, от которых зависит эта
    std::unordered_set<Position, PositionHash> dependents_;    // Ячейки, которые зависят от этой

    mutable std::optional<Value> cached_value_;  // Кэш вычисленного значения
    mutable bool cache_is_valid_ = false;

    // Вспомогательные методы
    void UpdateDependencies(const std::vector<Position>& new_deps);
    bool WouldCreateCycle(const Position& pos, std::unordered_set<Position, PositionHash>& visited) const;
};
