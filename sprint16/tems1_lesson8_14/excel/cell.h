#pragma once

#include "common.h"
#include "formula.h"

#include <memory>
#include <string>

class Cell : public CellInterface {
public:
    Cell();
    ~Cell();

    void Set(std::string text) override;
    void Clear();

    Value GetValue() const override;
    std::string GetText() const override;

private:
    class Impl;
    class EmptyImpl;
    class TextImpl;
    class FormulaImpl;

    std::unique_ptr<Impl> impl_;
};
