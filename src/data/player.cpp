#include "player.hpp"
#include "src/data/data-helpers.hpp"

Player::Player() {
    // TODO ?
}

Player::~Player() {
    // TODO ?
}

void Player::load(obs_data_t *data) {
    this->_name = ObsDataHelpers::getString(data, "name");
    this->_imagePath = ObsDataHelpers::getString(data, "imagePath");
}
