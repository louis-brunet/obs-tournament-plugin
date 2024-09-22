#pragma once

#include "src/data/player.hpp"
#include "src/data/tournament-reference.hpp"
#include "src/data/tournament-round.hpp"
#include <memory>
#include <obs-data.h>
#include <string>
#include <vector>

class Tournament {
public:
	enum Type {
		Unknown = -1,
		Custom = 0,
	};

	Tournament();
	Tournament(Tournament &&) = default;
	Tournament(const Tournament &) = default;
	Tournament &operator=(Tournament &&) = default;
	Tournament &operator=(const Tournament &) = default;
	~Tournament();

	Tournament::Type type() const;
	void setType(Tournament::Type type);

	std::string name() const;
	void setName(const char *name);

	std::vector<std::shared_ptr<Player>> &players();
	void setPlayers(std::vector<std::shared_ptr<Player>> &&players);

	// std::vector<TournamentRound> &rounds();

	void load(obs_data_t *data, const TournamentReference &reference);
	void save(obs_data_t *data) const;

private:
	std::string _name = "";
	std::vector<std::shared_ptr<Player>> _players = {};
	std::vector<std::shared_ptr<TournamentRound>> _rounds = {};
	Tournament::Type _type = Tournament::Tournament::Unknown;
};
