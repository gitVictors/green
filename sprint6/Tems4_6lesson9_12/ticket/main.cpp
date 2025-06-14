#include <algorithm>
#include <deque>
#include <string>
#include <iostream>

using namespace std;

struct Ticket {
    int id;
    string name;
};

class TicketOffice {
public:
    void PushTicket(const string& name) {
        tickets_.push_back({last_id_++, name});
    }

    int GetAvailable() const {
        return tickets_.size();
    }

    int GetAvailable(const string& name) const {
        return count_if(tickets_.begin(), tickets_.end(),
                        [&](const Ticket& t) { return t.name == name; });
    }

    void Invalidate(int minimum) {
        while (!tickets_.empty() && tickets_.front().id < minimum) {
            tickets_.pop_front();
        }
    }

private:
    int last_id_ = 0;
    deque<Ticket> tickets_;
};

int main() {
    TicketOffice tickets;

    tickets.PushTicket("Swan Lake"); // id - 0
    tickets.PushTicket("Swan Lake"); // id - 1
    tickets.PushTicket("Boris Godunov"); // id - 2
    tickets.PushTicket("Boris Godunov"); // id - 3
    tickets.PushTicket("Swan Lake"); // id - 4
    tickets.PushTicket("Boris Godunov"); // id - 5
    tickets.PushTicket("Boris Godunov"); // id - 6

    cout << tickets.GetAvailable() << endl; // Вывод: 7
    cout << tickets.GetAvailable("Swan Lake") << endl; // Вывод: 3
    cout << tickets.GetAvailable("Boris Godunov") << endl; // Вывод: 4

    tickets.Invalidate(3); // Удаляет билеты с id 0,1,2

    cout << tickets.GetAvailable() << endl; // Вывод: 4
    cout << tickets.GetAvailable("Swan Lake") << endl; // Вывод: 1
    cout << tickets.GetAvailable("Boris Godunov") << endl; // Вывод: 3

    tickets.PushTicket("Swan Lake"); // id - 7
    tickets.PushTicket("Swan Lake"); // id - 8

    cout << tickets.GetAvailable("Swan Lake") << endl; // Вывод: 3
}
