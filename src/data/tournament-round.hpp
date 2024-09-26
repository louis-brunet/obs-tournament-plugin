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
    void setName(std::string);

    const std::vector<std::shared_ptr<Match>> &matches() const;
    void addMatch(std::shared_ptr<Match> match);
    long long duplicateMatch(std::shared_ptr<Match> match);
    bool deleteMatch(std::shared_ptr<Match> match);
    bool swapPrevious(long long matchIndex);
    bool swapNext(long long matchIndex);

    std::shared_ptr<TournamentRound> duplicate() const;

    void load(obs_data_t *data);
    void save(obs_data_t *data) const;

private:
    std::string _name = "";
    std::vector<std::shared_ptr<Match>> _matches = {};
};
