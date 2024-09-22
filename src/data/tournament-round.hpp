#pragma once

#include "src/data/match.hpp"
#include <memory>
#include <obs-data.h>
#include <string>
#include <vector>

class TournamentRound {
public:
	TournamentRound();
	TournamentRound(TournamentRound &&) = default;
	TournamentRound(const TournamentRound &) = default;
	TournamentRound &operator=(TournamentRound &&) = default;
	TournamentRound &operator=(const TournamentRound &) = default;
	~TournamentRound();

	std::string name() const;
	std::vector<std::shared_ptr<Match>> &matches();

	void load(obs_data_t *data);
	void save(obs_data_t *data) const;

private:
	std::string _name = "";
	std::vector<std::shared_ptr<Match>> _matches = {};
};

// TournamentRound::TournamentRound() {
// }
//
// TournamentRound::~TournamentRound() {
// }
