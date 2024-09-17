#pragma once

#include "src/model/plugin-data-object.hpp"
class Tournament;

struct TournamentReference : public TournamentPluginDataObject {
	long long tournamentIndex;

public:
	Tournament *tournament() const;

	void save(obs_data_t *dataObj) const override;
	void load(obs_data_t *dataObj) override;
};
