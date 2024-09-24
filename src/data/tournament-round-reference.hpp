#pragma once

#include "src/data/tournament-reference.hpp"
#include "src/data/tournament-round.hpp"
#include <memory>
#include <obs-data.h>

class TournamentRoundReference {
public:
    TournamentRoundReference(
        TournamentReference tournamentReference = TournamentReference(),
        long long roundIndex = -1);
    TournamentRoundReference(TournamentRoundReference &&) = default;
    TournamentRoundReference(const TournamentRoundReference &) = default;
    TournamentRoundReference &operator=(TournamentRoundReference &&) = default;
    TournamentRoundReference &
    operator=(const TournamentRoundReference &) = default;
    ~TournamentRoundReference();
    inline bool operator==(const TournamentRoundReference &rhs) const
    {
        return std::tie(this->tournamentReference, this->roundIndex) ==
               std::tie(rhs.tournamentReference, rhs.roundIndex);
    };

    TournamentReference tournamentReference = TournamentReference();
    long long roundIndex = -1;

    std::shared_ptr<TournamentRound> round() const;

    void load(obs_data_t *data);
    void save(obs_data_t *data) const;
};
