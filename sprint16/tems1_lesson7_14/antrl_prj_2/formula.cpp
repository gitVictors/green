#include "formula.h"

#include "FormulaAST.h"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <sstream>

using namespace std::literals;

std::ostream& operator<<(std::ostream& output, const FormulaError& fe) {
    return output << "#ARITHM!";
}

namespace {
class Formula : public FormulaInterface {
public:
    // Реализуйте следующие методы:
    explicit Formula(std::string expression)
        : ast_(ParseFormulaAST(expression))
    {

    }

    Value Evaluate() const override {
        try {
            double result = ast_.Execute();
            return result;
        } catch (const FormulaError& e) {
            return e;
        } catch (const std::exception& e) {
            return FormulaError("Evaluation error: "s + e.what());
        }
    }

    std::string GetExpression() const override {
        std::ostringstream oss;
        ast_.PrintFormula(oss);
        return oss.str();
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
