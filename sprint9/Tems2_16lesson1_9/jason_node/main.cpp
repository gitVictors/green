#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

// не меняйте файлы json.h и json.cpp
#include "json.h"

using namespace std;

struct Spending {
    string category;
    int amount;
};

int CalculateTotalSpendings(const vector<Spending>& spendings) {
    return accumulate(
        spendings.begin(), spendings.end(), 0, [](int current, const Spending& spending){
            return current + spending.amount;
        });
}

string FindMostExpensiveCategory(const vector<Spending>& spendings) {
    assert(!spendings.empty());
    auto compare_by_amount = [](const Spending& lhs, const Spending& rhs) {
        return lhs.amount < rhs.amount;
    };
    return max_element(begin(spendings), end(spendings), compare_by_amount)->category;
}

vector<Spending> LoadFromJson(istream& input) {
    // место для вашей реализации
    // пример корректного JSON-документа в условии
    vector<Spending> result;
    Spending val;
    Document dc = Load (input);
    const Node& nd_root = dc.GetRoot();
    const auto itm  = nd_root.AsArray();

    for (const auto& it : itm){
        const auto&  it_mp = it.AsMap();
        val.amount = it_mp.at("amount").AsInt();
        val.category = it_mp.at("category").AsString();
        result.push_back(val);
    }

    return result;
}

int main() {
    // не меняйте main
    const vector<Spending> spendings = LoadFromJson(cin);
    cout << "Total "sv << CalculateTotalSpendings(spendings) << '\n';
    cout << "Most expensive is "sv << FindMostExpensiveCategory(spendings) << '\n';
}
