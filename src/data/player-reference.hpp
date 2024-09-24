#pragma once

#include "src/data/player.hpp"
#include "src/data/tournament-reference.hpp"
#include <obs-data.h>

class PlayerReference {
public:
	PlayerReference(TournamentReference tournamentReference = TournamentReference(), long long playerIndex = -1);
	PlayerReference(PlayerReference &&) = default;
	PlayerReference(const PlayerReference &) = default;
	PlayerReference &
	operator=(PlayerReference &&) = default;
	PlayerReference &
	operator=(const PlayerReference &) = default;
	~PlayerReference();

    TournamentReference tournamentReference = TournamentReference();
    long long playerIndex = -1;

    std::shared_ptr<Player> player() const;

    void load(obs_data_t *data);
    void save(obs_data_t *data) const;
};
