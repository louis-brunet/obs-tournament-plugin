#pragma once

#include "src/data/match-participant.hpp"
#include "src/data/player-reference.hpp"

class MatchParticipantPlayer : public MatchParticipant {
public:
    MatchParticipantPlayer();
    MatchParticipantPlayer(MatchParticipantPlayer &&) = default;
    MatchParticipantPlayer(const MatchParticipantPlayer &) = default;
    MatchParticipantPlayer &operator=(MatchParticipantPlayer &&) = default;
    MatchParticipantPlayer &operator=(const MatchParticipantPlayer &) = default;
    ~MatchParticipantPlayer();

    std::string displayName() const override;
    void load(obs_data_t *data) override;

private:
    PlayerReference _playerReference;
    std::string _displayName;
};
