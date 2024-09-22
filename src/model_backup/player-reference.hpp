#pragma once

#include "src/model/player.hpp"
#include "src/model/plugin-data-object.hpp"
#include "src/model/tournament-reference.hpp"

class PlayerReference: public TournamentPluginDataObject {
public:
    TournamentReference tournamentReference;
    long long playerIndex;

    PlayerReference(TournamentReference tournamentReference = TournamentReference(), long long playerIndex = -1);
    PlayerReference(PlayerReference &&) = default;
    PlayerReference(const PlayerReference &) = default;
    PlayerReference &operator=(PlayerReference &&) = default;
    PlayerReference &operator=(const PlayerReference &) = default;
    ~PlayerReference();

    Player *player() const;

	void save(obs_data_t *dataObj) const override;
	void load(obs_data_t *dataObj) override;
};
