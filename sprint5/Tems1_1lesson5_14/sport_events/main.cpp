#include "sport_events.h"

int main() {
    FootballMatch football_match_1{"Чемпионат Бразилии", "Рио-де-Жанейро", Team{.name="Фламенго", .city="Рио-де-Жанейро"}, Team{.name="Палмейрас", .city="Сан-Паулу"}};
    football_match_1.AddFootballScore(Player{.name="Роналду", .surname="Силва"}, 15, 1);
    football_match_1.AddFootballScore(Player{.name="Тиаго", .surname="Мораес"}, 32, 2);
    football_match_1.AddFootballScore(Player{.name="Фелипе", .surname="Гомеш"}, 34, 2);

    TennisMatch tennis_match_1{"Открытый чемпионат Австралии", "Мельбурн", Player{.name="Бенжамен", .surname="Бонзи"}, Player{.name="Давид", .surname="Гоффен"}};
    tennis_match_1.AddTennisScore(TennisScoreInfo{.player1_games=6, .player2_games=1});
    tennis_match_1.AddTennisScore(TennisScoreInfo{.player1_games=6, .player2_games=2});
    tennis_match_1.AddTennisScore(TennisScoreInfo{.player1_games=7, .player2_games=6});

    FigureSkatingEvent figure_scating_match_1{"Чемпионат Японии", "Токио"};
    figure_scating_match_1.AddFigureScore(FigureSkatingScoreInfo{.player=Player{.name="Каори", .surname="Сакамото"}, .score=228});
    figure_scating_match_1.AddFigureScore(FigureSkatingScoreInfo{.player=Player{.name="Мао", .surname="Шимада"}, .score=219});
    figure_scating_match_1.AddFigureScore(FigureSkatingScoreInfo{.player=Player{.name="Вакаба", .surname="Хигучи"}, .score=206});
    figure_scating_match_1.AddFigureScore(FigureSkatingScoreInfo{.player=Player{.name="Моне", .surname="Чиба"}, .score=205});

    FootballMatch football_match_2{"Серия А", "Милан", Team{.name="Ювентус", .city="Турин"}, Team{.name="Интер", .city="Милан"}};
    football_match_2.AddFootballScore(Player{.name="Леонардо", .surname="Бонуччи"}, 20, 1);
    football_match_2.AddFootballScore(Player{.name="Марио", .surname="Гёце"}, 29, 2);
    football_match_2.AddFootballScore(Player{.name="Федерико", .surname="Кьеза"}, 37, 1);

    TennisMatch tennis_match_2{"Открытый чемпионат США", "Нью-Йорк", Player{.name="Ига", .surname="Швентек"}, Player{.name="Арина", .surname="Соболенко"}};
    tennis_match_2.AddTennisScore(TennisScoreInfo{.player1_games=3, .player2_games=6});
    tennis_match_2.AddTennisScore(TennisScoreInfo{.player1_games=6, .player2_games=1});
    tennis_match_2.AddTennisScore(TennisScoreInfo{.player1_games=6, .player2_games=4});

    FigureSkatingEvent figure_scating_match_2{"Чемпионат России", "Омск"};
    figure_scating_match_2.AddFigureScore(FigureSkatingScoreInfo{.player=Player{.name="Владислав", .surname="Дикиджи"}, .score=297});
    figure_scating_match_2.AddFigureScore(FigureSkatingScoreInfo{.player=Player{.name="Глеб", .surname="Лутфуллин"}, .score=283});
    figure_scating_match_2.AddFigureScore(FigureSkatingScoreInfo{.player=Player{.name="Евгений", .surname="Семененко"}, .score=281});
    figure_scating_match_2.AddFigureScore(FigureSkatingScoreInfo{.player=Player{.name="Пётр", .surname="Гуменник"}, .score=278});

    FootballMatch football_match_3{"Чемпионат Франции", "Париж", Team{.name="Пари Сен-Жермен", .city="Париж"}, Team{.name="Монако", .city="Монако"}};
    football_match_3.AddFootballScore(Player{.name="Килиан", .surname="Мбаппе"}, 10, 1);
    football_match_3.AddFootballScore(Player{.name="Неймар", .surname="да Сильва"}, 25, 2);
    football_match_3.AddFootballScore(Player{.name="Эдинсон", .surname="Кавани"}, 42, 1);

    TennisMatch tennis_match_3{"Турнир серии Мастерс", "Мадрид", Player{.name="Рафаэль", .surname="Надаль"}, Player{.name="Карлос", .surname="Алькарас"}};
    tennis_match_3.AddTennisScore(TennisScoreInfo{.player1_games=6, .player2_games=2});
    tennis_match_3.AddTennisScore(TennisScoreInfo{.player1_games=4, .player2_games=6});
    tennis_match_3.AddTennisScore(TennisScoreInfo{.player1_games=3, .player2_games=6});

    FigureSkatingEvent figure_scating_match_3{"Чемпионат Франции", "Анси"};
    figure_scating_match_3.AddFigureScore(FigureSkatingScoreInfo{.player=Player{.name="Кевин", .surname="Аймоз"}, .score=264});
    figure_scating_match_3.AddFigureScore(FigureSkatingScoreInfo{.player=Player{.name="Франсуа", .surname="Пито"}, .score=231});
    figure_scating_match_3.AddFigureScore(FigureSkatingScoreInfo{.player=Player{.name="Люк", .surname="Экономидес"}, .score=213});
    figure_scating_match_3.AddFigureScore(FigureSkatingScoreInfo{.player=Player{.name="Корентин", .surname="Спинар"}, .score=203});

    ShowAllResults(std::cout, {
                                  &football_match_1,
                                  &tennis_match_1,
                                  &figure_scating_match_1,
                                  &football_match_2,
                                  &tennis_match_2,
                                  &figure_scating_match_2,
                                  &football_match_3,
                                  &tennis_match_3,
                                  &figure_scating_match_3,
                              });
}
