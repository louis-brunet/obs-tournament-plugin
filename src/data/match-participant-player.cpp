#include "match-participant-player.hpp"
#include "src/data/match-reference.hpp"
#include <obs.hpp>
#include <stdexcept>

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

MatchParticipant::ValidateConfigurationResult
MatchParticipantPlayer::validateConfiguration(
    const MatchReference &matchContext) const
{
    auto player = this->_playerReference.player();
    if (!player) {
        throw std::runtime_error(
            "[MatchParticipantPlayer::validateConfiguration] invalid player reference");
    }

    auto match = matchContext.match();
    if (!match) {
        throw std::runtime_error(
            "[MatchParticipantPlayer::validateConfiguration] invalid match reference");
    }

    std::shared_ptr<MatchParticipant> otherParticipant;
    if (match->participant1().get() == this) {
        otherParticipant = match->participant2();
    } else if (match->participant2().get() == this) {
        otherParticipant = match->participant1();
    } else {
        throw std::runtime_error(
            "[MatchParticipantPlayer::validateConfiguration] given match reference does not contain this participant");
    }

    if (otherParticipant->type() == MatchParticipant::Type::Player &&
        this->_playerReference ==
            std::reinterpret_pointer_cast<MatchParticipantPlayer>(
                otherParticipant)
                ->_playerReference) {
        return MatchParticipantPlayer::ValidateConfigurationResult::
            InvalidPlayerVersusSelf;
    }

    // TODO: if other is from match, traverse tree to check no player vs self

    return MatchParticipant::ValidateConfigurationResult::Valid;
}
