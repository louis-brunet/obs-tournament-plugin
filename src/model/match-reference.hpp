#pragma once

#include "src/model/plugin-data-object.hpp"
#include "src/model/tournament-reference.hpp"

class TournamentMatch;

class MatchReference: public TournamentPluginDataObject {
public:
    TournamentReference tournamentReference;
    long long matchIndex;

    MatchReference(TournamentReference tournamentReference = TournamentReference(), long long matchIndex = -1);
    MatchReference(MatchReference &&) = default;
    MatchReference(const MatchReference &) = default;
    MatchReference &operator=(MatchReference &&) = default;
    MatchReference &operator=(const MatchReference &) = default;
    ~MatchReference();

    TournamentMatch *match() const;

	void save(obs_data_t *dataObj) const override;
	void load(obs_data_t *dataObj) override;
};
