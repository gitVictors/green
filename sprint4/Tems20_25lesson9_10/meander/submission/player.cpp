#include "player.h"

void Player::Play(const std::vector<int16_t>& data) {
    buffer.close();
    audioByteArray = QByteArray(reinterpret_cast<const char*>(data.data()),
                              data.size() * sizeof(int16_t));

    buffer.setBuffer(&audioByteArray);
    buffer.open(QIODevice::ReadOnly);
    sink.start(&buffer);
}
