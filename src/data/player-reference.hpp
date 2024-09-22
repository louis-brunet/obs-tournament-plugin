#pragma once

#include "src/data/tournament-reference.hpp"
#include <obs-data.h>

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

    void load(obs_data_t *data);

private:
	TournamentReference tournamentReference;
	long long playerIndex;
};
