#include "player-reference.hpp"

#include "src/model/tournament.hpp"
#include "src/plugin-support.h"

PlayerReference::PlayerReference(TournamentReference _tournamentReference,
				 long long _playerIndex)
	: tournamentReference(_tournamentReference),
	  playerIndex(_playerIndex)
{
}

PlayerReference::~PlayerReference() {}

Player *PlayerReference::player() const
{
	auto tournament = this->tournamentReference.tournament();
	if (!tournament) {
		obs_log(LOG_INFO,
			"[PlayerReference::player] tournament is null, tournamentIndex=%d!",
			this->tournamentReference.tournamentIndex);
		return nullptr;
	}

	if (this->playerIndex < 0 ||
	    (unsigned long)this->playerIndex >= tournament->players.size()) {
		return nullptr;
	}
	return tournament->players.at((unsigned long)this->playerIndex);
}

void PlayerReference::save(obs_data_t *dataObj) const
{
	OBSDataAutoRelease tournamentData = obs_data_create();
	this->tournamentReference.save(tournamentData);
	obs_data_set_obj(dataObj, "tournamentReference", tournamentData);

	obs_data_set_int(dataObj, "playerIndex", this->playerIndex);
}

void PlayerReference::load(obs_data_t *dataObj)
{
	OBSDataAutoRelease tournamentData =
		obs_data_get_obj(dataObj, "tournamentReference");
	this->tournamentReference.load(tournamentData);

	obs_data_set_default_int(dataObj, "playerIndex", -1);
	this->playerIndex = obs_data_get_int(dataObj, "playerIndex");
}
