#pragma once

#include "src/data/match-participant.hpp"

class MatchParticipantUnknown : public MatchParticipant {
public:
    MatchParticipantUnknown();
    MatchParticipantUnknown(MatchParticipantUnknown &&) = default;
    MatchParticipantUnknown(const MatchParticipantUnknown &) = default;
    MatchParticipantUnknown &operator=(MatchParticipantUnknown &&) = default;
    MatchParticipantUnknown &
    operator=(const MatchParticipantUnknown &) = default;
    ~MatchParticipantUnknown();

    std::string displayName() const override;
    void load(obs_data_t *data) override;
    void save(obs_data_t *data) const override;
    std::shared_ptr<MatchParticipant> duplicate() const override;
    ValidateConfigurationResult
    validateConfiguration(const MatchReference &matchContext) const override;
    std::shared_ptr<Player> determinedPlayer() const override;

private:
};
