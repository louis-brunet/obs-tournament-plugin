#pragma once

#include <obs-data.h>
#include <string>

class Player {
public:
    Player();
    Player(Player &&) = default;
    Player(const Player &) = default;
    Player &operator=(Player &&) = default;
    Player &operator=(const Player &) = default;
    ~Player();

    std::string name();
    std::string imagePath();

    void load(obs_data_t *data);

private:
    std::string _name;
    std::string _imagePath;
};

// Player::Player() {
// }
//
// Player::~Player() {
// }
