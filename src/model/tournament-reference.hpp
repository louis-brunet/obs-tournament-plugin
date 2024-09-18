#pragma once

#include "src/model/plugin-data-object.hpp"
class Tournament;

class TournamentReference : public TournamentPluginDataObject {
public:
	long long tournamentIndex;

	TournamentReference(long long tournamentIndex = -1);
    TournamentReference(TournamentReference &&) = default;
    TournamentReference(const TournamentReference &) = default;
    TournamentReference &operator=(TournamentReference &&) = default;
    TournamentReference &operator=(const TournamentReference &) = default;
    ~TournamentReference();

	Tournament *tournament() const;

	void save(obs_data_t *dataObj) const override;
	void load(obs_data_t *dataObj) override;
};
