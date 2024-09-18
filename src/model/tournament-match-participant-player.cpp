#include "tournament-match-participant-player.hpp"
#include "src/plugin-support.h"
#include <obs.hpp>

TournamentMatchParticipantPlayer::TournamentMatchParticipantPlayer(
	PlayerReference __playerReference)
	// Player *__player)
	: TournamentMatchParticipant(
		  TournamentMatchParticipant::Type::StaticPlayer),
	  _playerReference(__playerReference)
{
	// this->_player = __player;
}

TournamentMatchParticipantPlayer::~TournamentMatchParticipantPlayer() {}

bool TournamentMatchParticipantPlayer::isValid() const
{
	return this->_playerReference.player() != nullptr;
}

bool TournamentMatchParticipantPlayer::isReady() const
{
	return this->isValid();
}

std::string TournamentMatchParticipantPlayer::displayName() const
{
    auto player = this->_playerReference.player();
    if (!player) {
        return obs_module_text("InvalidPlayerReference");
    }
	return player->name();
}

void TournamentMatchParticipantPlayer::save(obs_data_t *dataObj) const
{
	TournamentMatchParticipant::save(dataObj);

    OBSDataAutoRelease playerRefData = obs_data_create();
    this->_playerReference.save(playerRefData);
    obs_data_set_obj(dataObj, "playerReference", playerRefData);

	// if (this->_player) {
	// 	OBSDataAutoRelease playerData = obs_data_create();
	// 	this->_player->save(playerData);
	// 	obs_data_set_obj(dataObj, "player", playerData);
	// }
}

void TournamentMatchParticipantPlayer::load(obs_data_t *dataObj)
{
    TournamentMatchParticipant::load(dataObj);

	OBSDataAutoRelease playerReferenceData =
		obs_data_get_obj(dataObj, "playerReference");
	this->_playerReference.load(playerReferenceData);
}
