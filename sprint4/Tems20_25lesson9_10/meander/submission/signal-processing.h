#pragma once
#include <cstdint>
#include <vector>
#include <numbers>
#include <cassert>

#include <iterator>
#include <algorithm>
#include <QDebug>

enum class SignalType {
    kSin,
    kCos,
    kMeander
};

struct SignalData {
    SignalType signal_type; // Тип сигнала.
    int samples;            // Длина сигнала.
    int wave_length;        // Длина волны.
    int16_t amplitude;      // Максимальное значение.
    double cycle;           // Скважность меандра.
};


inline void ReplicateSignal(std::vector<int16_t>& signal, size_t desired_length) {

    assert(!signal.empty());

    size_t current_size = signal.size();;

    // Удваиваем размер, пока не достигнем или не превысим desired_length
    while (current_size < desired_length) {
        const size_t to_copy = std::min(current_size, desired_length - current_size);
        signal.insert(signal.end(), signal.begin(), signal.begin() + to_copy);
        current_size += to_copy;
    }

}


inline std::vector<int16_t> GenerateSignal(SignalData data) {
    // Создайте сигнал, имеющий нужные параметры.
    // Формула синусоидального сигнала: 
    // data.amplitude * sin(i * 2 * std::numbers::pi / data.wave_length).
    //
    // Формула косинусоидального сигнала: 
    // data.amplitude * cos(i * 2 * std::numbers::pi / data.wave_length).
    //
    // Меандр создайте через std::fill_n.
    // Количество положительных отсчётов для меандра можно вычислть как
    // static_cast<int>(data.cycle * data.wave_length).

    std::vector<int16_t> signal_r;
    signal_r.reserve(data.wave_length);

    switch (data.signal_type){
    case SignalType::kSin: {

        auto generator = [=, i=0 ]() mutable {
            return  static_cast<int16_t>( data.amplitude * sin( i++ * 2 * std::numbers::pi / data.wave_length) );
        };

        std::generate_n(std::back_inserter(signal_r), data.wave_length,  generator);

        break;
    }

    case SignalType::kCos:
    {

        auto generator = [=, i=0 ]() mutable {
            return  static_cast<int16_t>( data.amplitude * cos( i++ * 2 * std::numbers::pi / data.wave_length) );
        };

        std::generate_n(std::back_inserter(signal_r), data.wave_length,  generator);

        break;
    }
    case SignalType::kMeander :
    {
        signal_r.reserve(data.wave_length);
        const int positive_samples = static_cast<int>(data.cycle * data.wave_length);
        std::fill_n(std::back_inserter(signal_r), positive_samples, data.amplitude);
        std::fill_n(std::back_inserter(signal_r), data.wave_length - positive_samples, -data.amplitude);
    }
        break;
    default:
        break;
    }


    ReplicateSignal (signal_r, data.samples);


    return signal_r;
}



inline void ApplyDecayAndAttack(std::vector<int16_t>& signal, size_t max_length) {

    if (signal.empty() || max_length == 0) return;


    // Apply decay (конец сигнала)
    const size_t decay_length = std::min(max_length, signal.size());
    size_t n = decay_length;  // Счетчик для transform


    auto start_pos = signal.end() - decay_length;
    std::transform(
        start_pos,
        signal.end(),
        start_pos,
        [&n, decay_length](int16_t sample) mutable {
            const double factor =   static_cast<double>(n) / static_cast<double>(decay_length);
            //qDebug() << "Decay: n =" << n << "factor =" << factor ; //<< "sample =" << sample;
            n--;
            return static_cast<int16_t>(sample * factor);
        }
        );

    // // Apply attack (начало сигнала)
    const size_t attack_length = std::min(max_length, signal.size());
      n = 0;  // Счетчик для transform

    std::transform(
        signal.begin(),
        signal.begin() + attack_length,
        signal.begin(),
        [&n, attack_length](int16_t sample) {
            const double factor = static_cast<double>(n) / static_cast<double>(attack_length );
            n++;
           // qDebug() << "Attack: n =" << n << "factor =" << factor << "sample =" << sample;
            return static_cast<int16_t>(sample * factor);
        }
        );




}


