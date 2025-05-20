#include <vector>
#include <optional>
#include <string>
#include <algorithm>
#include <numeric>

struct Package {
    std::string sender{};
    std::string addressee{};
    double weight = 0;
};

class Post {
public:
    Post() = default;

    // У почтового отделения есть ограничение на количество посылок.
    void SetPostCapacity(size_t capacity) {
        packages_.reserve(capacity);
        capacity_ = capacity;
    }

    // Функция добавления посылки.
    void AddPackage(const std::string& sender, const std::string& addressee, double weight) {
        if (GetFreePlace() <= 0) {
            return;
        }
        packages_.push_back(Package{
            .sender = sender,
            .addressee = addressee,
            .weight = weight
        });
    }

    double CalculateAverageWeight() {
        if (packages_.empty())
            return 0.0;
        double sum = CalculateTotalWeight();
        return sum / packages_.size();
    }

    std::optional<Package> FindHeaviestPackage() {

        if (packages_.empty())
            return std::nullopt;

        auto it = std::max_element (packages_.begin(), packages_.end(), [](const Package &a, const Package &b ){
            return a.weight < b.weight;
                                  });

        return *it;
    }

    std::optional<Package> FindLightestPackage() {
        if (packages_.empty())
            return std::nullopt;

        auto it = std::max_element (packages_.begin(), packages_.end(), [](const Package &a, const Package &b ){
            return a.weight > b.weight;
        });

        return *it;
    }

    double CalculateTotalWeight() {
        return std::accumulate(packages_.begin(), packages_.end(), 0.0, [](double sum, const Package& wd) {
            return sum + wd.weight;
        });
    }

    std::optional<Package> FindFirstSenderByAddress(const std::string& address) {

        auto it = std::find_if (packages_.begin(), packages_.end(), [&address](const Package& a){
            return a.addressee == address;
        } );

        if (it !=  packages_.end()){
            return *it;
        }

        return  std::nullopt;
    }

    int CalculatePackageForAddress(const std::string& address) {
        int count = 0;
        for (const auto& package : packages_) {
            if (package.addressee == address) {
                count++;
            }
        }
        return count;
    }

private:
    int GetFreePlace() {
        return capacity_ - HowManyPackages();
    }

    size_t HowManyPackages() {
        return packages_.size();
    }

private:
    std::vector<Package> packages_;
    size_t capacity_ = 0;
};
