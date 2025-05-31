#pragma once

template <typename View, typename Model>
class Controller {
public:
    Controller(View& view, Model& model, int winning_score = 3) :
        view_(view),
        model_(model),
        winning_score_(winning_score),
        score_(0) {}

    void StartGame() {
        while (score_ < winning_score_) {
            view_.PrintBoard(model_.GetHopperPosition(), model_.GetFlyPosition(), model_.GetBoardSize());
            int hops = view_.GetUserInput();
            model_.SetGrasshopperPosition(hops);
            if (model_.CheckCatch()) {
                score_++;
            } else {
                score_--;
            }
            view_.ShowScore(score_);
        }
        view_.ShowWinMessage();
    }

private:
    View& view_;
    Model& model_;
    const int winning_score_;
    int score_;
};