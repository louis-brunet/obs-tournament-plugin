#include "match-participant-player.hpp"
#include "src/data/data-helpers.hpp"
#include <obs.hpp>
#include <stdexcept>

MatchParticipantPlayer::MatchParticipantPlayer() : MatchParticipant() {}

MatchParticipantPlayer::~MatchParticipantPlayer() {}

std::string MatchParticipantPlayer::displayName() const
{
	throw std::runtime_error("TODO MatchParticipantPlayer::displayName()");
}

void MatchParticipantPlayer::load(obs_data_t *data) {
	MatchParticipant::load(data);

    this->_displayName = ObsDataHelpers::getString(data, "displayName");

    OBSDataAutoRelease playerReferenceData = obs_data_get_obj(data, "playerReference");
    this->_playerReference.load(playerReferenceData);
}
