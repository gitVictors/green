#pragma once

class TV {
public:
    TV();

    void TurnOn();
    void TurnOff();
    bool IsTurnedOn();
    void SetChannel(int chan);
    int GetCurrent() const;
    int GetMaxChan() const;
    int GetMinChan() const;

private:
    bool is_on_;
    int current_channel_;
    const int min_channel_;
    const int max_channel_;
};