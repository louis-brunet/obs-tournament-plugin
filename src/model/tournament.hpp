#pragma once

#include "src/model/plugin-data-object.hpp"
#include "src/model/player.hpp"
#include "src/model/tournament-match.hpp"
#include "src/model/tournament-reference.hpp"
#include <memory>
#include <obs-data.h>
#include <vector>

class Tournament : public TournamentPluginDataObject {
public:
	enum Type {
		SingleEliminationKnockoutTournamentType = 0,
		CustomKnockoutTournamentType,
	};

	// static Tournament *load(obs_data_t *dataObj);
	static Tournament *loadStatic(obs_data_t *dataObj);
	static Tournament::Type loadType(obs_data_t *dataObj);

	~Tournament();

	virtual void save(obs_data_t *dataObj) const override;
	virtual void load(obs_data_t *dataObj) override;

	std::vector<std::unique_ptr<Player>> players;
	Tournament::Type type;
	std::vector<TournamentMatch *> matches;

protected:
	Tournament(const Tournament::Type type,
		   std::vector<std::unique_ptr<Player>> &&players, TournamentReference reference);
		   // const std::vector<Player *> &players);
    TournamentReference reference;

// private:
};
