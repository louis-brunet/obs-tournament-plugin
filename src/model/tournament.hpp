#pragma once

#include "src/model/player-reference.hpp"
#include "src/model/plugin-data-object.hpp"
#include "src/model/player.hpp"
#include "src/model/tournament-match.hpp"
#include "src/model/tournament-reference.hpp"
#include <obs-data.h>
#include <vector>

class Tournament : public TournamentPluginDataObject {
public:
    enum Type {
        SingleEliminationKnockoutTournamentType = 0,
        CustomKnockoutTournamentType,
    };

	// static Tournament *load(obs_data_t *dataObj);
	// static Tournament *loadStatic(obs_data_t *dataObj);
	static Tournament::Type loadType(obs_data_t *dataObj);

	virtual ~Tournament();

	// std::vector<std::unique_ptr<Player>> players;
	std::vector<Player *> players;
	Tournament::Type type;
	std::vector<TournamentMatch *> matches;
	TournamentReference reference;
    std::vector<PlayerReference> playerReferences();
    std::vector<MatchReference> matchReferences();

	virtual void save(obs_data_t *dataObj) const override;
	virtual void load(obs_data_t *dataObj) override;

protected:
	Tournament(const Tournament::Type type,
		   std::vector<Player *> &&_players,
		   // std::vector<std::unique_ptr<Player>> &&players,
		   TournamentReference reference);
    Tournament(Tournament &&) = default;
    Tournament(const Tournament &) = default;
    Tournament &operator=(Tournament &&) = default;
    Tournament &operator=(const Tournament &) = default;
	// const std::vector<Player *> &players);

	// private:
};
