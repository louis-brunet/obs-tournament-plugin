#pragma once

#include "src/data/tournament-round-reference.hpp"

class MatchReference {
public:
    MatchReference();
    MatchReference(MatchReference &&) = default;
    MatchReference(const MatchReference &) = default;
    MatchReference &operator=(MatchReference &&) = default;
    MatchReference &operator=(const MatchReference &) = default;
    ~MatchReference();

private:
    TournamentRoundReference roundReference;
    long long matchIndex;
};

// MatchReference::MatchReference() {
// }
//
// MatchReference::~MatchReference() {
// }
