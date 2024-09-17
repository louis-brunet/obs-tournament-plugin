#include "tournament-match-participant-player.hpp"
#include "src/plugin-support.h"
#include <obs.hpp>

TournamentMatchParticipantPlayer::TournamentMatchParticipantPlayer(
	Player *__player)
	: TournamentMatchParticipant(
		  TournamentMatchParticipant::Type::StaticPlayer)
{
	this->_player = __player;
}

TournamentMatchParticipantPlayer::~TournamentMatchParticipantPlayer() {}

bool TournamentMatchParticipantPlayer::isValid() const
{
	return this->_player != nullptr;
}

bool TournamentMatchParticipantPlayer::isReady() const
{
	return this->isValid();
}

std::string TournamentMatchParticipantPlayer::displayName() const
{
	return this->_player->name();
}

void TournamentMatchParticipantPlayer::save(obs_data_t *dataObj) const
{
    TournamentMatchParticipant::save(dataObj);
	if (this->_player) {
		OBSDataAutoRelease playerData = obs_data_create();
		this->_player->save(playerData);
		obs_data_set_obj(dataObj, "player", playerData);
	}
}

void TournamentMatchParticipantPlayer::load(obs_data_t *dataObj)
{
    TournamentMatchParticipant::load(dataObj);
	obs_log(LOG_INFO, "[TournamentMatchParticipantPlayer::load] called");
	if (!dataObj) {
		return;
	}

	OBSDataAutoRelease playerData = obs_data_get_obj(dataObj, "player");
	this->_player = Player::loadStatic(playerData);
}
