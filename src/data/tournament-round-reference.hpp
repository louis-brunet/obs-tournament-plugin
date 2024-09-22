#pragma once

#include "src/data/tournament-reference.hpp"

class TournamentRoundReference {
public:
	TournamentRoundReference();
	TournamentRoundReference(TournamentRoundReference &&) = default;
	TournamentRoundReference(const TournamentRoundReference &) = default;
	TournamentRoundReference &
	operator=(TournamentRoundReference &&) = default;
	TournamentRoundReference &
	operator=(const TournamentRoundReference &) = default;
	~TournamentRoundReference();

private:
	TournamentReference tournamentReference = TournamentReference();
	long long roundIndex = -1;
};

// TournamentRoundReference::TournamentRoundReference() {}
//
// TournamentRoundReference::~TournamentRoundReference() {}
