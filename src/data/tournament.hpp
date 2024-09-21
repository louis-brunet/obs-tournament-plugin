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
	Tournament();
	Tournament(Tournament &&) = default;
	Tournament(const Tournament &) = default;
	Tournament &operator=(Tournament &&) = default;
	Tournament &operator=(const Tournament &) = default;
	~Tournament();

	std::string name() const;
    std::vector<std::shared_ptr<Player>> &players() const;
    std::vector<TournamentRound> &rounds() const;

    void load(obs_data_t *data, const TournamentReference &reference);
    // void save(obs_data_t *data) const;

private:
    std::string _name;
    std::vector<std::shared_ptr<Player>> _players;
    std::vector<std::shared_ptr<TournamentRound>> _rounds;
};


// TournamentReference::TournamentReference() {
// }
//
// TournamentReference::~TournamentReference() {
// }
