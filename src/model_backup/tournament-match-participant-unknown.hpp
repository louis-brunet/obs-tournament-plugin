#pragma once

#include "src/model/tournament-match-participant.hpp"

class TournamentMatchParticipantUnknown : public TournamentMatchParticipant {
public:
	TournamentMatchParticipantUnknown();
	~TournamentMatchParticipantUnknown();

    ValidateResult validate() const override;
    // bool isValid() const override;
    bool isReady() const override;
    std::string displayName() const override;

    void save(obs_data_t *dataObj) const override;
    void load(obs_data_t *dataObj) override;
};

