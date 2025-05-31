#include <iostream>
#include <cassert>


const int MIN_CHANNEL = 1;
const int MAX_CHANNEL = 99;

/* Допишите класс в соответствии с требованиями задания. */
class TV {
public:
    // Включает телевизор.
    void TurnOn() {
        is_tv_on_ = true;
    }

    // Выключает телевизор.
    void TurnOff() {
        is_tv_on_ = false;
    }

    // Возвращает true, если телевизор включён, и false, если телевизор выключен.
    bool IsTurnedOn() {
        
        return is_tv_on_;
    }

    // Возвращает номер текущего канала либо 0, если телевизор был выключен.
    // Номер канала не сбрасывается при выключении и повторном включении.
    // При первом включении телевизор показывает канал № 1.
    int GetCurrentChannel() {
        if (is_tv_on_ == false)
            return 0;
        
        return number_channel_;
    }

    // Выбирает канал с указанным номером. Номер канала должен быть в диапазоне [1..99].
    // Если указан недопустимый номер канала или телевизор выключен, возвращает false и не меняет
    // текущий канал. В противном случае возвращает true.
    bool SelectChannel(int channel) {
        if (is_tv_on_ == false)
            return false;

        if (  (channel >= 1) && (channel <= 99) ){
            number_channel_ = channel;
            return true;
        }else { 
            return false;
        }
    }
private:
    bool is_tv_on_ = false;
    int number_channel_ = 1;

};

int main() {


    TV tv;
    tv.TurnOn();
    for (auto i = 0; i < 10; ++i) {
        int channel = (641 * i) % MAX_CHANNEL + 1;
        assert(tv.SelectChannel(channel));
        assert(tv.GetCurrentChannel() == channel);
        tv.TurnOff();
        assert(!tv.IsTurnedOn());
        tv.TurnOn();
        assert(tv.GetCurrentChannel() == channel);
    }

}