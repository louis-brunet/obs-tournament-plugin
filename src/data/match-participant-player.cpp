#include "match-participant-player.hpp"
#include <obs.hpp>

MatchParticipantPlayer::MatchParticipantPlayer(PlayerReference playerReference)
    : MatchParticipant(MatchParticipant::Type::Player),
      _playerReference(playerReference)
{
}

MatchParticipantPlayer::~MatchParticipantPlayer() {}

std::string MatchParticipantPlayer::displayName() const
{
    auto player = this->_playerReference.player();
    if (player) {
        return player->name();
    }
    return "[INVALID PLAYER REF]";
}

PlayerReference MatchParticipantPlayer::playerReference() const
{
    return this->_playerReference;
}

void MatchParticipantPlayer::load(obs_data_t *data)
{
    MatchParticipant::load(data);

    // this->_displayName = ObsDataHelpers::getString(data, "displayName");

    OBSDataAutoRelease playerReferenceData =
        obs_data_get_obj(data, "playerReference");
    this->_playerReference.load(playerReferenceData);
}

void MatchParticipantPlayer::save(obs_data_t *data) const
{
    MatchParticipant::save(data);

    // obs_data_set_string(data, "displayName", this->_displayName);

    OBSDataAutoRelease playerReferenceData = obs_data_create();
    this->_playerReference.save(playerReferenceData);
    obs_data_set_obj(data, "playerReference", playerReferenceData);
}

std::shared_ptr<MatchParticipant> MatchParticipantPlayer::duplicate() const
{
    return std::make_shared<MatchParticipantPlayer>(*this);
}
