#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class SportEvent {
    // Реализуйте самостоятельно.
public:

    SportEvent(const std::string& name, const std::string& city)
        : name_(name), city_(city) {}

    virtual ~SportEvent() = default;

     virtual void ShowResults(std::ostream& out) const = 0;

    std::string GetName () const {
        return name_;

    }

    std::string GetCity () const {
        return city_;
    }

private:
    std::string name_;
    std::string city_;

};

inline void ShowAllResults(std::ostream& out, std::vector<SportEvent*> events_ptrs) {
    int i = 0;
    for (auto event : events_ptrs) {
        out << "Информация о соревновании #" << ++i << std::endl;
        event->ShowResults(out);
        out << std::endl;
    }
}

struct Player {
    std::string name;
    std::string surname;

    friend std::ostream& operator<<(std::ostream& out, const Player& player) {
        out << player.surname << " " << player.name;
        return out;
    }
};

// Структуры для класса с футбольными матчами:
struct Team {
    std::string name;
    std::string city;

    friend std::ostream& operator<<(std::ostream& out, const Team& team) {
        out << team.name << " (" << team.city << ")";
        return out;
    }
};

struct FootballScoreInfo {
    Player player;      // Игрок, забивший гол.
    const Team* team;   // Из какой команды.
    int time_in_min;    // На какой минуте.

    friend std::ostream& operator<<(std::ostream& out, const FootballScoreInfo& info) {
        out << info.time_in_min << " минута: " << info.player
            << " из команды " << *info.team;
        return out;
    }
};

struct TennisScoreInfo {
    int player1_games;
    int player2_games;

    friend std::ostream& operator<<(std::ostream& out, const TennisScoreInfo& info) {
        out << " - " << info.player1_games << "-" << info.player2_games;
        return out;
    }
};

struct FigureSkatingScoreInfo {
    Player player;
    int score;

    friend std::ostream& operator<<(std::ostream& out, const FigureSkatingScoreInfo& info) {
        out << info.player << " " << info.score << " баллов";
        return out;
    }
};

class FootballMatch : public SportEvent {
public:
    FootballMatch(const std::string& name, const std::string& city, const Team& t1, const Team& t2)
        : SportEvent(name, city), team1_(t1), team2_(t2) {}

    void AddFootballScore(const Player& player, int time_in_min, int team) {
        scores_info_.push_back(FootballScoreInfo{
                                                 .player = player,
                                                 .team = team == 1 ? &team1_ : &team2_,
                                                 .time_in_min = time_in_min});
        if (team == 1) {
            ++score_team1_;
        } else {
            ++score_team2_;
        }
    }

    void ShowResults(std::ostream& out) const override {
        out << "Футбольный турнир: " <<  GetName() << "\n";
        out << "Город проведения матча: " << GetCity() << "\n";
        out << "Команды: " << team1_ << " vs " << team2_ << "\n";
        out << "Счёт: " << score_team1_ << " - " << score_team2_ << "\n";
        if (score_team1_ == score_team2_) {
            out << "Ничья\n";
        } else {
            out << "Победила команда: "
                << (score_team2_ > score_team1_ ? team2_ : team1_) << "\n";
        }
        out << "Игроки, забившие голы: ";
        for (const auto& score : scores_info_) {
            out << score << std::endl;
        }
    }

private:
    Team team1_;
    Team team2_;
    std::vector<FootballScoreInfo> scores_info_;
    int score_team1_ = 0;
    int score_team2_ = 0;
};

class TennisMatch : public SportEvent {
public:
        // Реализуйте класс самостоятельно.

    TennisMatch (std::string name, std::string cyti, Player pl1, Player  pl2) :
        SportEvent(name, cyti),
        player1_(pl1),
        player2_(pl2),
        player1_sets_(0),
        player2_sets_(0)
    {}

    void ShowResults( std::ostream& out) const override{
        out << "Теннисный турнир: " << GetName() << "\n";
        out << "Город проведения матча: " <<  GetCity() << "\n" ;
        out << "Игроки: " << player1_ << " vs " << player2_ << "\n";
        out << "Счёт по сетам: " << "\n";
        for (const auto& inf : sets_){
            out << inf << "\n";

        }
       out << "Победитель: " << (player1_sets_ > player2_sets_ ? player1_ : player2_) << "\n";
    }

    void AddTennisScore (TennisScoreInfo tnInfo){
        sets_.push_back(tnInfo);
        if (tnInfo.player1_games > tnInfo.player2_games) {
            player1_sets_++;
        } else {
            player2_sets_++;
        }
    }

private:
    Player player1_;
    Player player2_;
    int player1_sets_;
    int player2_sets_;
    std::vector<TennisScoreInfo> sets_;

};

class FigureSkatingEvent : public SportEvent {
public:

    FigureSkatingEvent(const std::string& name, const std::string& city)
        : SportEvent(name, city) {}

    // Реализуйте класс самостоятельно.
    void ShowResults(std::ostream& out) const override {
        out << "Соревнование по фигурному катанию: " << GetName() << "\n";
        out << "Город проведения соревнования: " << GetCity() << "\n";
        out << "Участники и баллы:\n";
        for (const auto& score : scores_) {
            out << score << "\n";
        }
    }


    void AddFigureScore(const FigureSkatingScoreInfo& score) {
        scores_.push_back(score);
        std::sort(scores_.begin(), scores_.end(),
                  [](const FigureSkatingScoreInfo& a, const FigureSkatingScoreInfo& b) {
                      return a.score > b.score;
                  });
    }




private:
    std::vector<FigureSkatingScoreInfo> scores_;

};


