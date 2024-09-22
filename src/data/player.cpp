#include "player.hpp"
#include "src/data/data-helpers.hpp"

Player::Player(std::string name, std::string imagePath)
	: _name(name),
	  _imagePath(imagePath)
{
	// TODO ?
}

Player::~Player()
{
	// TODO ?
}

void Player::load(obs_data_t *data)
{
	this->_name = ObsDataHelpers::getString(data, "name");
	this->_imagePath = ObsDataHelpers::getString(data, "imagePath");
}

void Player::save(obs_data_t *data) const
{
	obs_data_set_string(data, "name", this->_name.c_str());
	obs_data_set_string(data, "imagePath", this->_imagePath.c_str());
}
