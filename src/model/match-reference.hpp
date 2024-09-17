#pragma once

#include "src/model/plugin-data-object.hpp"
#include "src/model/tournament-reference.hpp"

class TournamentMatch;

class MatchReference: public TournamentPluginDataObject {

public:
    TournamentReference tournamentReference;
    long long matchIndex;

    TournamentMatch *match() const;

	void save(obs_data_t *dataObj) const override;
	void load(obs_data_t *dataObj) override;
};
