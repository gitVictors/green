#include "vector_of_pairs.h"
#include <cassert>

int main() {
    {
        VectorOfPairs<std::string, int> bank_accounts;

        bank_accounts.SetValueByKey("Elon", 90000000);
        bank_accounts.SetValueByKey("Bill", 10000000);
        bank_accounts.SetValueByKey("Jeff", 99999999);
        bank_accounts.SetValueByKey("Mark", 1234567);

        using Vector = decltype(bank_accounts.GetUnderlying());
        assert((bank_accounts.GetUnderlying() == Vector{
                                                        {"Elon", 90000000},
                                                        {"Bill", 10000000},
                                                        {"Jeff", 99999999},
                                                        {"Mark", 1234567},
                                                        }));

        bank_accounts.SetValueByKey("Bill", 20000000);
        bank_accounts.SetValueByKey("Mark", 98766767);
        using Vector = decltype(bank_accounts.GetUnderlying());
        assert((bank_accounts.GetUnderlying() == Vector{
                                                        {"Elon", 90000000},
                                                        {"Bill", 20000000},
                                                        {"Jeff", 99999999},
                                                        {"Mark", 98766767},
                                                        }));

        bank_accounts.SetValueByKey("Larry", 111111111);
        assert((bank_accounts.GetUnderlying() == Vector{
                                                        {"Elon", 90000000},
                                                        {"Bill", 20000000},
                                                        {"Jeff", 99999999},
                                                        {"Mark", 98766767},
                                                        {"Larry", 111111111},
                                                        }));
    }

    {
        VectorOfPairs<int, std::string> telegram_users;

        telegram_users.SetValueByKey(11111, "Fir");
        telegram_users.SetValueByKey(22222, "Annie");
        telegram_users.SetValueByKey(33333, "Pumpkin");
        using Vector = decltype(telegram_users.GetUnderlying());
        assert((telegram_users.GetUnderlying() == Vector{
                                                         {11111, "Fir"},
                                                         {22222, "Annie"},
                                                         {33333, "Pumpkin"},
                                                         }));

        telegram_users.SetValueByKey(44444, "Tony");
        telegram_users.SetValueByKey(55555, "Jarvis");
        using Vector = decltype(telegram_users.GetUnderlying());
        assert((telegram_users.GetUnderlying() == Vector{
                                                         {11111, "Fir"},
                                                         {22222, "Annie"},
                                                         {33333, "Pumpkin"},
                                                         {44444, "Tony"},
                                                         {55555, "Jarvis"},
                                                         }));

        telegram_users.SetValueByKey(55555, "Friday");
        using Vector = decltype(telegram_users.GetUnderlying());
        assert((telegram_users.GetUnderlying() == Vector{
                                                         {11111, "Fir"},
                                                         {22222, "Annie"},
                                                         {33333, "Pumpkin"},
                                                         {44444, "Tony"},
                                                         {55555, "Friday"},
                                                         }));
    }
}
