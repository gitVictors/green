#pragma once

#include <QAudioFormat>
#include <QAudioOutput>
#include <QMediaDevices>
#include <QAudioDevice>
#include <QMediaPlayer>
#include <QAudioSink>
#include <QBuffer>

#include <vector>
#include <cstdint>

class Player {
public:
    Player() {}

    void Play(const std::vector<int16_t>& data);

private:
    static QAudioFormat GetFormat() {
        QAudioFormat format;

        format.setSampleRate(48000);
        format.setChannelCount(1); // Mono.
        format.setSampleFormat(QAudioFormat::Int16); // 16 bits.

        return format;
    }

private:
    QAudioFormat format = GetFormat();

    QAudioDevice defaultDevice = QMediaDevices::defaultAudioOutput();
    // Create the audio output.
    // QAudioOutput audioOutput{defaultDevice};
    QAudioSink sink{defaultDevice, format};

    // Create a QBuffer to hold the audio data.
    QByteArray audioByteArray;

    // Create a QBuffer to hold the audio data.
    QBuffer buffer;
};
