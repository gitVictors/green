
#include <iostream>
#include <vector>
#include <functional>


class ActionsLogger
{
public:
    ActionsLogger()
    {
        for (int i = 0; i < 4; ++i)
        {
            auto& calls_link = this->calls;
            actions.emplace_back(
                [&calls_link, i](){++calls_link[i];}
                );
        }
    };

    void clear()
    {
        calls = {0, 0, 0, 0};
    }

    bool checkActionCorrectness(int expected_action)
    {
        for (int i = 0; i < 4; ++ i)
        {
            if (calls[i] != 0 and i != expected_action)
                return false;
        }
        return true;
    }

    bool checkActionCalls(int expected_action)
    {
        return calls[expected_action] == 1;
    }
    std::function<void ()> getAction(int index)
    {
        return actions[index];
    }
private:
    std::vector<int> calls = {0, 0, 0, 0};
    std::vector<std::function<void()>> actions;
};
