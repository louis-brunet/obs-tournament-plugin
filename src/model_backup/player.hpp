#pragma once

#include "src/model/plugin-data-object.hpp"
#include <obs-data.h>
#include <string>

class Player: public TournamentPluginDataObject {
public:
    static Player *loadStatic(obs_data_t *dataObj);

	Player(const std::string name = "<UNNAMED>");
    Player(Player &&) = default;
    Player(const Player &) = default;
    Player &operator=(Player &&) = default;
    Player &operator=(const Player &) = default;
	~Player() = default;

	std::string name();

	void save(obs_data_t *dataObj) const override;
	void load(obs_data_t *dataObj) override;

private:
	std::string _name;
};
