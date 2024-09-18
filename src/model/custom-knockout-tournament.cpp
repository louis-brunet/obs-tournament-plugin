#include "custom-knockout-tournament.hpp"

CustomKnockoutTournament::CustomKnockoutTournament(
	TournamentReference __reference, std::vector<Player *> &&__players)
	: Tournament(Tournament::Type::CustomKnockoutTournamentType,
		     std::move(__players), __reference),
	  _isStarted(false)
{
}

//     CustomKnockoutTournament::CustomKnockoutTournament(
// 	const std::vector<Player *> &__players)
// 	: Tournament(Tournament::Type::CustomKnockoutTournamentType, __players)
// {
// 	this->_isStarted = false;
// }

CustomKnockoutTournament::~CustomKnockoutTournament() {}

bool CustomKnockoutTournament::isStarted() const
{
	return this->_isStarted;
}

void CustomKnockoutTournament::start() {
    this->_isStarted = true;
    // TODO: any other start modifications?
}

void CustomKnockoutTournament::save(obs_data_t *dataObj) const
{
	Tournament::save(dataObj);
	obs_data_set_bool(dataObj, "isStarted", this->_isStarted);
}

void CustomKnockoutTournament::load(obs_data_t *dataObj)
{
	Tournament::load(dataObj);
	obs_data_set_default_bool(dataObj, "isStarted", false);
	this->_isStarted = obs_data_get_bool(dataObj, "isStarted");
}

// CustomKnockoutTournament *
// CustomKnockoutTournament::loadStatic(obs_data_t *dataObj)
// {
//     auto t = new CustomKnockoutTournament();
//     t->load(dataObj);
//     return t;
// }
