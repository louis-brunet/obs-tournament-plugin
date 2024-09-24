#pragma once

#include "src/data/match-participant.hpp"
#include "src/data/player-reference.hpp"

class MatchParticipantPlayer : public MatchParticipant {
public:
    MatchParticipantPlayer(PlayerReference playerReference = PlayerReference());
    MatchParticipantPlayer(MatchParticipantPlayer &&) = default;
    MatchParticipantPlayer(const MatchParticipantPlayer &) = default;
    MatchParticipantPlayer &operator=(MatchParticipantPlayer &&) = default;
    MatchParticipantPlayer &operator=(const MatchParticipantPlayer &) = default;
    ~MatchParticipantPlayer();

    std::string displayName() const override;
    PlayerReference playerReference() const;

    void load(obs_data_t *data) override;
    void save(obs_data_t *data) const override;
    std::shared_ptr<MatchParticipant> duplicate() const override;

private:
    PlayerReference _playerReference;
    // std::string _displayName;
};
