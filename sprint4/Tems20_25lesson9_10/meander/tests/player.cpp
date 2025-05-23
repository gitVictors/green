#include "player.h"

extern std::vector<int16_t> player_data;

void Player::Play(const std::vector<int16_t>& data) {
    player_data = data;
}
