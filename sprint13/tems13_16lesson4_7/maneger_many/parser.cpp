#include "parser.h"

#include <unordered_map>

namespace queries {

class ComputeIncome : public ComputeQuery {
public:
    using ComputeQuery::ComputeQuery;

    [[nodiscard]] ReadResult Process(const BudgetManager &budget) const override {
        const int idx_from = BudgetManager::GetDayIndex(GetFrom());
        const int idx_to = BudgetManager::GetDayIndex(GetTo());

        double net_income = 0;

        for (int i = idx_from; i <= idx_to; ++i) {
            const auto& day = budget.GetDayState(i);
            net_income += day.income - day.spending; //  Учитываем и доход, и траты
        }

        return {net_income};
    }

    class Factory : public QueryFactory {
    public:
        [[nodiscard]] std::unique_ptr<Query> Construct(std::string_view config) const override {
            auto parts = Split(config, ' ');
            return std::make_unique<ComputeIncome>(Date(parts[0]), Date(parts[1]));
        }
    };
};

class Alter : public ModifyQuery {
public:
    Alter(Date from, Date to, double amount)
        : ModifyQuery(from, to), amount_(amount) {
    }

    void Process(BudgetManager& budget) const override {
        const int idx_from = BudgetManager::GetDayIndex(GetFrom());
        const int idx_to = BudgetManager::GetDayIndex(GetTo());

        double day_income = amount_ / (idx_to - idx_from + 1);

        for (int i = idx_from; i <= idx_to; ++i) {
            budget.GetDayState(i).income += day_income;
        }
    }

    class Factory : public QueryFactory {
    public:
        [[nodiscard]] std::unique_ptr<Query> Construct(std::string_view config) const override {
            auto parts = Split(config, ' ');
            double payload = std::stod(std::string(parts[2]));
            return std::make_unique<Alter>(Date(parts[0]), Date(parts[1]), payload);
        }
    };

private:
    double amount_;
};

class PayTax : public ModifyQuery {
public:
    using ModifyQuery::ModifyQuery;

    PayTax(Date from, Date to, double tax_rate = 13.0)  // Добавляем параметр по умолчанию
        : ModifyQuery(from, to), tax_rate_(tax_rate) {
    }

    void Process(BudgetManager& budget) const override {
        budget.PayTax(GetFrom(), GetTo(), tax_rate_);
    }

    // void Process(BudgetManager& budget) const override {
    //     const int idx_from = BudgetManager::GetDayIndex(GetFrom());
    //     const int idx_to = BudgetManager::GetDayIndex(GetTo());

    //     for (int i = idx_from; i <= idx_to; ++i) {
    //         budget.GetDayState(i).income *= 0.87;
    //     }
    // }

    class Factory : public QueryFactory {
    public:
        [[nodiscard]] std::unique_ptr<Query> Construct(std::string_view config) const override {
            auto parts = Split(config, ' ');
            if (parts.size() == 2) {
                // Старая версия: PayTax from to (без указания процента)
                return std::make_unique<PayTax>(Date(parts[0]), Date(parts[1]));
            } else {
                // Новая версия: PayTax from to rate
                double tax_rate = std::stod(std::string(parts[2]));
                return std::make_unique<PayTax>(Date(parts[0]), Date(parts[1]), tax_rate);
            }
        }
    };

private:
    double tax_rate_;
};

class Spend : public ModifyQuery {
public:
    Spend(Date from, Date to, double amount)
        : ModifyQuery(from, to), amount_(amount) {
    }

    void Process(BudgetManager& budget) const override {
        budget.SpendMoney(GetFrom(), GetTo(), amount_);
    }

    class Factory : public QueryFactory {
    public:
        [[nodiscard]] std::unique_ptr<Query> Construct(std::string_view config) const override {
            auto parts = Split(config, ' ');
            double payload = std::stod(std::string(parts[2]));
            return std::make_unique<Spend>(Date(parts[0]), Date(parts[1]), payload);
        }
    };

private:
    double amount_;
};

// class PayTaxWithRate : public ModifyQuery {
// public:
//     PayTaxWithRate(Date from, Date to, double tax_rate)
//         : ModifyQuery(from, to), tax_rate_(tax_rate) {
//     }

//     void Process(BudgetManager& budget) const override {
//         budget.PayTax(GetFrom(), GetTo(), tax_rate_);
//     }

//     class Factory : public QueryFactory {
//     public:
//         [[nodiscard]] std::unique_ptr<Query> Construct(std::string_view config) const override {
//             auto parts = Split(config, ' ');
//             double tax_rate = std::stod(std::string(parts[2]));
//             return std::make_unique<PayTaxWithRate>(Date(parts[0]), Date(parts[1]), tax_rate);
//         }
//     };

// private:
//     double tax_rate_;
// };


}  // namespace queries

const QueryFactory& QueryFactory::GetFactory(std::string_view id) {
    using namespace std::literals;

    static queries::ComputeIncome::Factory compute_income;
    static queries::Alter::Factory alter;
    static queries::PayTax::Factory pay_tax;
    static queries::Spend::Factory spend;       // Для команды Spend

    static std::unordered_map<std::string_view, const QueryFactory &> factories
        = {{"ComputeIncome"sv, compute_income},
           {"Earn"sv,          alter},
           {"PayTax"sv,        pay_tax},
           {"Spend"sv,         spend},          // Регистрируем новую команду
            };

    return factories.at(id);
}
