#include "sheet.h"

#include "cell.h"
#include "common.h"

#include <algorithm>
#include <functional>
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

    // Создаем новую ячейку или получаем существующую
    auto& cell_ptr = cells_[pos];
    if (!cell_ptr) {
        cell_ptr = std::make_unique<Cell>();
    }

    // Устанавливаем текст ячейки
    cell_ptr->Set(std::move(text));

    // Инвалидируем кеш размера
    InvalidateCache();
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
        InvalidateCache();
    }
}

Size Sheet::GetPrintableSize() const {

    if (!cached_size_.has_value()) {
        cached_size_ = CalculatePrintableSize();
    }
    return cached_size_.value();
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
