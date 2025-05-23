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

inline void ApplyDecayAndAttack(std::vector<int16_t>& signal,
                                size_t max_length);

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

inline void ReplicateSignal_m(std::vector<int16_t>& signal, size_t desired_length) {
    size_t wave_length = signal.size();
    while (signal.size() < desired_length) {
        size_t max_insert = desired_length - signal.size();
        size_t to_insert = std::min(wave_length, max_insert);

        // В цикле будем добавлять по 200 элементов.
        std::copy_n(signal.begin(), to_insert, std::back_inserter(signal));
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

   // if (signal_r.size() < data.samples )
         ReplicateSignal (signal_r, data.samples);

  //   ApplyDecayAndAttack(signal_r, 12000);

    return signal_r;
}

inline void applyDecay_my(std::vector<int16_t>& signal, size_t max_length) {
    const size_t decay_length = std::min(signal.size(), max_length);

    for(size_t i = decay_length; i > 0; --i) {
        int16_t& sample = signal[signal.size() - i];
        const double factor = static_cast<double>(i) / static_cast<double>(decay_length);
        sample = static_cast<int16_t>(sample * factor);
    }
}

inline void applyAttack_my(std::vector<int16_t>& signal, size_t max_length) {
    const size_t attack_length = std::min(signal.size(), max_length);

    for(size_t i = 0; i < attack_length; ++i) {
        int16_t& sample = signal[i];
        const double factor = static_cast<double>(i) / static_cast<double>(attack_length);
        sample = static_cast<int16_t>(sample * factor);
    }
}

inline void ApplyDecayAndAttack(std::vector<int16_t>& signal, size_t max_length) {

    if (signal.empty() || max_length == 0) return;

    // // Apply attack (начало сигнала)
    // const size_t attack_length = std::min(max_length, signal.size());
    //  size_t n = 0;  // Счетчик для transform

    // std::transform(
    //     signal.begin(),
    //     signal.begin() + attack_length,
    //     signal.begin(),
    //     [&n, attack_length](int16_t sample) {
    //         const double factor = static_cast<double>(n) / static_cast<double>(attack_length );
    //         n++;
    //        // qDebug() << "Attack: n =" << n << "factor =" << factor << "sample =" << sample;
    //         return static_cast<int16_t>(sample * factor);
    //     }
    //     );

    // // Apply decay (конец сигнала)
    // const size_t decay_length = std::min(max_length, signal.size());
    // n = decay_length;  // Счетчик для transform


    // auto start_pos = signal.end() - decay_length;
    // std::transform(
    //     start_pos,
    //     signal.end(),
    //     start_pos,
    //     [&n, decay_length](int16_t sample) mutable {
    //         const double factor =   static_cast<double>(n) / static_cast<double>(decay_length);
    //         //qDebug() << "Decay: n =" << n << "factor =" << factor ; //<< "sample =" << sample;
    //         if (n>0) n--;
    //         return static_cast<int16_t>(sample * factor);
    //     }
    //     );

    applyAttack_my(signal, max_length);
    applyDecay_my(signal, max_length);
}


// inline void ApplyDecayAndAttack(std::vector<int16_t>& signal,
//                                 size_t max_length) {
//     // Примените затухание и атаку сигнала.
//     // Используйте принцип, данный в уроке.
//     // Затухание применяется к концу сигнала, а
//     // атака симметрично - к началу.
//     // Используйте алгоритм transform.

//     if (signal.empty() || max_length == 0) return;

//     // Apply attack (начало сигнала)
//     const size_t attack_length = std::min(max_length, signal.size());
//     size_t n = 0;

//     auto transformer = [&n, attack_length] (int16_t sample) mutable {
//         double factor = static_cast<double>(n++) / static_cast<double>(attack_length-1);
//         return static_cast<int16_t>(sample * factor );
//     };

//     std::transform(
//         signal.begin(),
//         signal.begin() + attack_length,
//         signal.begin(),
//         transformer );



//     // // Apply decay (конец сигнала)
//     const size_t decay_length = std::min(max_length, signal.size());
//     n = decay_length;

//     auto trans_end = [&n, decay_length ] (int16_t sample) mutable {
//             const double factor = static_cast<double> (--n) / static_cast<double>(decay_length);
//             return static_cast<int16_t>(sample * factor );
//         };

//     std::transform(
//         signal.rbegin(),
//         signal.rbegin() +  decay_length,
//         signal.rbegin(),
//         trans_end );

// }
