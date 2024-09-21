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
    std::vector<Match> &matches() const;

    void load(obs_data_t *data);

private:
    std::string _name;
    std::vector<std::shared_ptr<Match>> _matches;
};


// TournamentRound::TournamentRound() {
// }
//
// TournamentRound::~TournamentRound() {
// }
