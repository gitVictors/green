#include "formula.h"

#include "FormulaAST.h"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <sstream>

using namespace std::literals;

// inline std::ostream& operator<<(std::ostream& output, const FormulaError& fe) {
//     return output << "#ARITHM!";
// }

namespace {
class Formula : public FormulaInterface {
public:
    // Реализуйте следующие методы:
    explicit Formula(std::string expression) 
    : ast_(ParseFormulaAST(expression)) 
    {

    }

    Value Evaluate(const SheetInterface& sheet) const override {  // ИСПРАВЛЕНО: добавлен параметр sheet
        try {
            // Создаем функцию для получения значения ячейки
            auto get_cell_value = [&sheet](Position pos) -> double {
                auto* cell = sheet.GetCell(pos);
                if (!cell) {
                    return 0.0; // Пустая ячейка трактуется как 0
                }

                auto value = cell->GetValue();
                if (std::holds_alternative<double>(value)) {
                    return std::get<double>(value);
                } else if (std::holds_alternative<std::string>(value)) {
                    const auto& text = std::get<std::string>(value);
                    if (text.empty()) {
                        return 0.0; // Пустой текст трактуется как 0
                    }

                    // Пытаемся преобразовать текст в число
                    try {
                        size_t pos;
                        double result = std::stod(text, &pos);
                        // Проверяем, что вся строка была преобразована
                        if (pos == text.size()) {
                            return result;
                        }
                    } catch (const std::exception&) {
                        // Если преобразование не удалось, бросаем ошибку значения
                        throw FormulaError(FormulaError::Category::Value);
                    }

                    throw FormulaError(FormulaError::Category::Value);
                } else {
                    // Если ячейка содержит ошибку, пробрасываем её
                    throw std::get<FormulaError>(value);
                }
            };

            double result = ast_.Execute(get_cell_value);  // ИСПРАВЛЕНО: передаем функцию
            return result;

        } catch (const FormulaError& e) {
            return e;
        } catch (const std::exception& e) {
            return FormulaError(FormulaError::Category::Value);
        }
    }
    
    std::string GetExpression() const override {
        std::ostringstream oss;
        ast_.PrintFormula(oss);
        return oss.str();
    }

    std::vector<Position> GetReferencedCells() const override {  // ДОБАВЛЕНО: реализация метода
        auto cells = ast_.GetCells();
        std::vector<Position> result(cells.begin(), cells.end());
        std::sort(result.begin(), result.end());
        result.erase(std::unique(result.begin(), result.end()), result.end());
        return result;
    }

private:
    FormulaAST ast_;
};
}  // namespace

std::unique_ptr<FormulaInterface> ParseFormula(std::string expression) {
    try {
        return std::make_unique<Formula>(std::move(expression));
    } catch (const ParsingError& e) {
        throw FormulaException("Formula parsing error: "s + e.what());
    } catch (const FormulaException& e) {
        throw;
    } catch (const std::exception& e) {
        throw FormulaException("Formula error: "s + e.what());
    }
}
