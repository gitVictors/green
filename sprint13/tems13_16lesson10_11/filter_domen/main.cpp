#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>


using namespace std;


class Domain {
public:
    // Конструктор, принимающий строку
    Domain(const std::string& domain) {
        // Здесь можно добавить логику для инициализации домена
        domain_ = std::string(domain.rbegin(), domain.rend()) + ".";
    }

    // Оператор сравнения на равенство
    bool operator==(const Domain& other) const {
        return other.domain_ == domain_;
    }

    // Оператор сравнения для сортировки
    bool operator<(const Domain& other) const {
        return domain_ < other.domain_;
    }

    // Метод для проверки, является ли данный домен поддоменом другого домена
    bool IsSubdomain(const Domain& parent) const {
        // Используем lexicographical_compare для проверки, является ли текущий домен поддоменом родительского домена
        return std::lexicographical_compare(
            domain_.begin(), domain_.end(),
            parent.domain_.begin(), parent.domain_.end(),
            [](char l, char r) {
                // Считаем точку самым маленьким символом
                return (r != '.') && (l < r || l == '.');
            }
            );

    }


    string GetDomain() const {
        return domain_;
    }

private:
    std::string domain_;

};




class DomainChecker {
public:
    template <typename InputIt>
    DomainChecker(InputIt begin, InputIt end) {
        // Сохраняем все запрещённые домены в вектор
        std::vector<Domain> all_domains(begin, end);

        // Сортируем домены для дальнейшего удобства работы
        std::sort(all_domains.begin(), all_domains.end());

        // Удаляем избыточные поддомены
        sorted_domains_ = AbsorbSubdomains(std::move(all_domains));
    }


    bool IsForbidden(const Domain& domain) const {
        auto it = upper_bound(sorted_domains_.begin(), sorted_domains_.end(), domain, [](const Domain& lhs, const Domain& rhs){
            return lhs.GetDomain() < rhs.GetDomain();
        });
        if (it == sorted_domains_.begin()) return false;
        else return domain.IsSubdomain(*prev(it));
    }


private:
    std::vector<Domain> AbsorbSubdomains(std::vector<Domain> domains) {
        domains.erase(std::unique(begin(domains), end(domains),
                                  [](const Domain& lhs, const Domain& rhs) {
                                      return lhs.IsSubdomain(rhs) || rhs.IsSubdomain(lhs);
                                  }),
                      end(domains));
        return domains;
    }



private:
    std::vector<Domain> sorted_domains_;
};



// разработайте функцию ReadDomains, читающую заданное количество доменов из стандартного входа

std::vector<Domain> ReadDomains(std::istream& input, size_t n) {

    std::vector<Domain> result_vector;
    result_vector.reserve(n);

    for (size_t i = 0; i < n; ++i) {
        std::string domain;
        getline(input, domain);

        result_vector.push_back(Domain(domain));
    }

    return result_vector;
}

template <typename Number>
Number ReadNumberOnLine(istream& input) {
    string line;
    getline(input, line);

    Number num;
    std::istringstream(line) >> num;

    return num;
}

int main() {
    const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}
