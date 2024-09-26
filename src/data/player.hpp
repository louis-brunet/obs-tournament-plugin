#pragma once

#include <obs-data.h>
#include <string>

class Player {
public:
    Player(std::string name = "", std::string imagePath = "", std::string description = "");
    Player(Player &&) = default;
    Player(const Player &) = default;
    Player &operator=(Player &&) = default;
    Player &operator=(const Player &) = default;
    ~Player();

    std::string name();
    std::string imagePath();
    std::string description();

    void load(obs_data_t *data);
    void save(obs_data_t *data) const;

private:
    std::string _name;
    std::string _imagePath;
    std::string _description;
};

// Player::Player() {
// }
//
// Player::~Player() {
// }
