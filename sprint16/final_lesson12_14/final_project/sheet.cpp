#include "sheet.h"
#include "cell.h"
// #include "common.h"

#include <algorithm>
// #include <functional>
#include <iostream>
#include <optional>
#include <vector>
#include <memory>
#include <unordered_map>

using namespace std::literals;

Sheet::~Sheet() {}


void Sheet::SetCell(Position pos, std::string text) {

    if (!pos.IsValid()) {
        throw InvalidPositionException("Invalid position");
    }

    // Ищем ячейку
    auto it = cells_.find(pos);
    if (it != cells_.end()) {
        // Ячейка существует
        it->second->Set(std::move(text));
    } else {
        // Создаем новую ячейку
        cells_[pos] = std::make_unique<Cell>(*this, pos);
        cells_[pos]->Set(std::move(text));
    }
}

const CellInterface* Sheet::GetCell(Position pos) const {
    if (!pos.IsValid()) {
        throw InvalidPositionException("Invalid position");
    }

    auto it = cells_.find(pos);
    if (it == cells_.end()) {
        return nullptr;
    }
    return it->second.get();
}

CellInterface* Sheet::GetCell(Position pos) {
    if (!pos.IsValid()) {
        throw InvalidPositionException("Invalid position");
    }

    auto it = cells_.find(pos);
    if (it == cells_.end()) {
        return nullptr;
    }
    return it->second.get();
}

void Sheet::ClearCell(Position pos) {

    if (!pos.IsValid()) {
        throw InvalidPositionException("Invalid position");
    }

    auto it = cells_.find(pos);
    if (it != cells_.end()) {
        cells_.erase(it);

    }
}

Size Sheet::GetPrintableSize() const {
     return CalculatePrintableSize();
}

Size Sheet::CalculatePrintableSize() const {

    if (cells_.empty()) {
        return {0, 0};
    }

    int max_row = -1;
    int max_col = -1;

    for (const auto& [pos, cell] : cells_) {
        if (cell && !cell->GetText().empty()) {
            max_row = std::max(max_row, pos.row);
            max_col = std::max(max_col, pos.col);
        }
    }

    return {max_row + 1, max_col + 1};
}

void Sheet::PrintValues(std::ostream& output) const {
    Print(output, true);
}

void Sheet::PrintTexts(std::ostream& output) const {
    Print(output, false);
}

void Sheet::Print(std::ostream& output, bool print_values) const {
    Size size = GetPrintableSize();

    for (int row = 0; row < size.rows; ++row) {
        for (int col = 0; col < size.cols; ++col) {
            if (col > 0) {
                output << '\t';
            }

            Position pos{row, col};
            auto it = cells_.find(pos);
            if (it != cells_.end() && it->second) {
                const auto& cell = it->second;
                if (print_values) {
                    // Печать значений
                    auto value = cell->GetValue();
                    if (std::holds_alternative<std::string>(value)) {
                        output << std::get<std::string>(value);
                    } else if (std::holds_alternative<double>(value)) {
                        output << std::get<double>(value);
                    } else if (std::holds_alternative<FormulaError>(value)) {
                        // output << std::get<FormulaError>(value).what();
                        output << std::get<FormulaError>(value);
                    }
                } else {
                    // Печать текстов
                    output << cell->GetText();
                }
            }
            // Для пустых ячеек ничего не выводим
        }
        output << '\n';
    }
}

std::unique_ptr<SheetInterface> CreateSheet() {
    return std::make_unique<Sheet>();
}
