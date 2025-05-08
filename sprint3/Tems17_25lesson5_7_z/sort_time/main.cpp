#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>
#include <format>
#include <string>

// День будет начинаться в 9 утра.
static const int MORNING_OFFSET = 9 * 60;

struct Task {
    std::string name; // Название задачи.
    int duration;     // Длительность задачи в минутах.
    int index;        // Индекс очерёдности задачи.
};

void PrintTask(const Task& task, int current_time) {
    int real_time = current_time + MORNING_OFFSET;
    int hours = real_time / 60;
    int minutes = real_time % 60;
    std::cout << std::format("{:02}:{:02} - {}",
                             hours, minutes, task.name) << std::endl;
}

std::vector<Task> BuildTimetableFor(const std::vector<Task>& source_tasks) {

    std::vector<Task> var_tasks = source_tasks;

    //сортировка по возростанию
    auto compare = [](const Task& s_lhs, const Task& s_rhs){
        if (s_lhs.index != s_rhs.index )
            return s_lhs.index < s_rhs.index;
        return s_lhs.name < s_rhs.name; //лексеграфически по возрастанию
    };

    std::sort(var_tasks.begin(), var_tasks.end(), compare);

    return var_tasks;
}

void PrintTimetable(const std::vector<Task>& tasks) {

     int current_time = 0;

    for (const auto& tsk : tasks){
        PrintTask(tsk, current_time);
        current_time += tsk.duration;
    }

}

void ProcessTimetable(const std::vector<Task>& tasks) {

    std::vector<Task> var_tsk = BuildTimetableFor(tasks);
    PrintTimetable(var_tsk);
}

int main() {
    std::vector<Task> tasks;
    int duration;
    int index;

    while (std::cin >> index >> duration >> std::ws) {
        std::string name;
        std::getline(std::cin, name);
        tasks.push_back(Task{
            .name = name,
            .duration = duration,
            .index = index
        });
    }

    ProcessTimetable(tasks);
}
