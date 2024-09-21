#include "tournament-match-participant-player.hpp"
#include <obs-module.h>
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

TournamentMatchParticipant::ValidateResult
TournamentMatchParticipantPlayer::validate(MatchReference &matchReference) const
{
	if (this->_playerReference.player() == nullptr) {
		// auto result = TournamentMatchParticipant::ValidateResult(TournamentMatchParticipant::ValidateResult::Type::Invalid);
		// result.
		TournamentMatchParticipant::ValidateResult::InvalidData data{
			.message = obs_module_text(
				"Error.TournamentMatchParticipantPlayer.InvalidPlayerReference")};
		return TournamentMatchParticipant::ValidateResult(data);
		// return TournamentMatchParticipant::ValidateResult{
		// 	.type = TournamentMatchParticipant::ValidateResult::
		// 		Type::Invalid,
		// 		.invalid = {
		// 			.message = obs_module_text(
		// 				"Error.TournamentMatchParticipant.MissingPlayer")}};
	}
    ....TODO check if other player is this player ? do i really need to switch on the other participant's type ? probably

	TournamentMatchParticipant::ValidateResult::ValidData data{};
	return TournamentMatchParticipant::ValidateResult(data);
	// return TournamentMatchParticipant::ValidateResult{
	// 	.type = TournamentMatchParticipant::ValidateResult::Type::Valid,
	// 	.valid = {}};
}
// bool TournamentMatchParticipantPlayer::isValid() const
// {
// 	return this->_playerReference.player() != nullptr;
// }

bool TournamentMatchParticipantPlayer::isReady() const
{
	auto a = this->validate();
	return this->validate().isValid();
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
