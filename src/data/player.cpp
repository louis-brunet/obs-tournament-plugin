#include "player.hpp"
#include "src/data/data-helpers.hpp"

Player::Player(std::string name, std::string imagePath, std::string description)
    : _name(name),
      _imagePath(imagePath),
      _description(description)
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
    this->_description = ObsDataHelpers::getString(data, "description");
}

void Player::save(obs_data_t *data) const
{
    obs_data_set_string(data, "name", this->_name.c_str());
    obs_data_set_string(data, "imagePath", this->_imagePath.c_str());
    obs_data_set_string(data, "description", this->_description.c_str());
}

std::string Player::name()
{
    return this->_name;
}

std::string Player::description()
{
    return this->_description;
}

std::string Player::imagePath()
{
    return this->_imagePath;
}
