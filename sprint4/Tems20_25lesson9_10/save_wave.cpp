#include <numbers>
#include <vector>

#include <QString>
#include <QFile>
#include <QDataStream>
#include <QCoreApplication>

template<class T>
struct WavHeader {
    constexpr static quint32 k_riff_id = 0x46464952;
    constexpr static quint32 k_wave_format = 0x45564157;
    constexpr static quint32 k_fmt_id = 0x20746d66;
    constexpr static quint32 k_data_id = 0x61746164;
    // RIFF
    quint32 chunk_id = k_riff_id;
    quint32 chunk_size = sizeof(WavHeader) - 8;
    quint32 chunk_format = k_wave_format;
    // fmt
    quint32 fmt_id = k_fmt_id;
    quint32 fmt_size = 8 * sizeof(T);
    quint16 audio_format = 1;
    quint16 num_channels = 1;
    quint32 sample_rate = 48000;
    quint32 byte_rate = sample_rate * sizeof(T);
    quint16 block_align = sizeof(T);
    quint16 bits_per_sample = 8 * sizeof(T);
    // data
    quint32 data_id = k_data_id;
    quint32 data_size;
};

void SaveWave(const QString &fileName, const std::vector<int16_t> &audio_data, int sample_rate) {
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Failed to open file for writing");
        return;
    }

    QDataStream out(&file);
    out.setByteOrder(QDataStream::LittleEndian);

    quint32 subchunk_size = static_cast<quint32>(audio_data.size() * sizeof(short));
    quint32 chunk_size = 36 + subchunk_size;

    WavHeader<int16_t> h{.chunk_size = quint32(chunk_size), .sample_rate=quint32(sample_rate), .data_size = quint32(subchunk_size)};

    out << h.chunk_id << h.chunk_size
        << h.chunk_format
        << h.fmt_id << h.fmt_size
        << h.audio_format
        << h.num_channels
        << h.sample_rate
        << h.byte_rate
        << h.block_align
        << h.bits_per_sample
        << h.data_id << h.data_size;

    for (const auto &sample : audio_data) {
        out << sample;
    }

    file.close();
}

void ReplicateSignal(std::vector<int16_t>& signal, size_t desired_length) {
    size_t wave_length = signal.size();
    while (signal.size() < desired_length) {
        size_t max_insert = desired_length - signal.size();
        size_t to_insert = std::min(wave_length, max_insert);

        // В цикле будем добавлять по 200 элементов.
        std::copy_n(signal.begin(), to_insert, std::back_inserter(signal));
    }
}

void ApplyDecay(std::vector<int16_t>& signal, size_t max_length) {
    size_t decay_length = std::min(signal.size(), max_length);

    for(size_t i = 0; i < decay_length; ++i) {
        int16_t& sample = signal[signal.size() - decay_length + i];
        double factor = double(decay_length - i) / decay_length;
        sample = static_cast<int16_t>(sample * factor);
    }
}

void ApplyDecay2(std::vector<int16_t>& signal, size_t max_length) {
    size_t decay_length = std::min(signal.size(), max_length);

    auto transformer = [=, i = decay_length](int16_t source) mutable {
        double factor = double(i--) / decay_length;
        return static_cast<int16_t>(source * factor);
    };

    auto start_pos = signal.end() - decay_length;
    std::transform(start_pos, signal.end(), start_pos, transformer);
}

int main(int argc, char *argv[]) {
    std::vector<int16_t> signal;
    signal.reserve(48000);

    const double amplitude = 15000;
    const int wave_length = 200;

    auto generator = [=, i = 0]() mutable {
        return amplitude * sin(2 * i++ * std::numbers::pi / wave_length);
    };

    std::generate_n(std::back_inserter(signal), wave_length, generator);

    ReplicateSignal(signal, 48000);
    ApplyDecay2(signal, 48000 / 1000 * 100);

    SaveWave("sinus.wav", signal, 48000); // Save as WAV
}