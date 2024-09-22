#pragma once

#include "src/data/tournament-round-reference.hpp"
#include <obs-data.h>

class MatchReference {
public:
    MatchReference();
    MatchReference(MatchReference &&) = default;
    MatchReference(const MatchReference &) = default;
    MatchReference &operator=(MatchReference &&) = default;
    MatchReference &operator=(const MatchReference &) = default;
    ~MatchReference();

    void load(obs_data_t *data);

private:
    TournamentRoundReference roundReference;
    long long matchIndex;
};

// MatchReference::MatchReference() {
// }
//
// MatchReference::~MatchReference() {
// }
