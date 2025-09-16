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
        // Простая проверка: если текущий домен начинается с родительского
        if (domain_.size() < parent.domain_.size()) {
            return false;
        }
        return domain_.substr(0, parent.domain_.size()) == parent.domain_;
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
        std::vector<Domain> all_domains(begin, end);
        std::sort(all_domains.begin(), all_domains.end());
        sorted_domains_ = RemoveSubdomains(std::move(all_domains));
    }

    bool IsForbidden(const Domain& domain) const {
        auto it = std::upper_bound(sorted_domains_.begin(), sorted_domains_.end(), domain);
        if (it != sorted_domains_.begin()) {
            --it;
            if (domain.IsSubdomain(*it)) {
                return true;
            }
        }
        return false;
    }

private:
    std::vector<Domain> RemoveSubdomains(std::vector<Domain> domains) {
        if (domains.empty()) return domains;

        std::vector<Domain> result;
        result.push_back(domains[0]);

        for (size_t i = 1; i < domains.size(); ++i) {
            // Добавляем только если текущий домен не является поддоменом последнего добавленного
            if (!domains[i].IsSubdomain(result.back())) {
                result.push_back(domains[i]);
            }
        }
        return result;
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
