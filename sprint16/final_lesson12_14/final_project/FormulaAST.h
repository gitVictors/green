#pragma once

#include "FormulaLexer.h"
#include "common.h"
#include "cell.h"

#include <forward_list>
#include <functional>
#include <stdexcept>

namespace ASTImpl {
class Expr;
}

class ParsingError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class FormulaAST {
public:
    explicit FormulaAST(std::unique_ptr<ASTImpl::Expr> root_expr);

    explicit FormulaAST(std::unique_ptr<ASTImpl::Expr> root_expr, std::forward_list<Position> cells);

    FormulaAST(FormulaAST&&) = default;
    FormulaAST& operator=(FormulaAST&&) = default;
    ~FormulaAST();

    void PrintCells(std::ostream& out) const ;
    double Execute() const;
    void Print(std::ostream& out) const;
    void PrintFormula(std::ostream& out) const;

    std::forward_list<Position> GetCells() const;
    double Execute(std::function<double(Position)> get_cell_value) const;

private:
    std::unique_ptr<ASTImpl::Expr> root_expr_;
    std::forward_list<Position> cells_;
};

FormulaAST ParseFormulaAST(std::istream& in);
FormulaAST ParseFormulaAST(const std::string& in_str);
