#include <queue>

// Это заготовка класса для отслеживания событий в интервале interval_.
// Можно добавлять новые методы (лучше приватные), члены класса и новый код.
// Нельзя менять интерфейс существующих методов.
class EventCounter {
public:
    // В конструкторе вы получаете интервал, события в котором нужно будет считать
    // и начальное время.
    EventCounter(const int interval, const int initial_time = 0):
        interval_(interval),
        current_time_(initial_time)
    {
    }

    // Вам предстоит реализовать следующие три метода.
    void UpdateTime(const int time) {
        if (time < current_time_)
        return;

        current_time_ = time;
        // Удаляем устаревшие события
        while (!events_.empty() && events_.front() < current_time_ - interval_) {
            events_.pop();
        }

    }

    void OnEvent() {
           // Добавляем событие с текущим временем
        events_.push(current_time_);
    }

    size_t EventsInInterval() const {
            size_t count = 0;
        std::queue<int> temp = events_;
        while (!temp.empty()) {
            if (temp.front() >= current_time_ - interval_) {
                count++;
            }
            temp.pop();
        }
        return count;
    }

private:
    const int interval_;
    int current_time_;
    std::queue<int> events_;
};