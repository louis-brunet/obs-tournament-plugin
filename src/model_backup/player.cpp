#include "player.hpp"

Player::Player(std::string playerName)
{
	this->_name = playerName;
}

std::string Player::name()
{
	return this->_name;
}

Player *Player::loadStatic(obs_data_t *dataObj) {
    auto p = new Player();
    p->load(dataObj);
    return p;
}

void Player::load(obs_data_t *dataObj)
{
    this->_name = obs_data_get_string(dataObj, "name");
}

void Player::save(obs_data_t *dataObj) const
{
	obs_data_set_string(dataObj, "name", this->_name.c_str());
}
