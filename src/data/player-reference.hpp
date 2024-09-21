#pragma once

#include "src/data/tournament-reference.hpp"

class PlayerReference {
public:
	PlayerReference();
	PlayerReference(PlayerReference &&) = default;
	PlayerReference(const PlayerReference &) = default;
	PlayerReference &
	operator=(PlayerReference &&) = default;
	PlayerReference &
	operator=(const PlayerReference &) = default;
	~PlayerReference();

private:
	TournamentReference tournamentReference;
	long long playerIndex;
};
