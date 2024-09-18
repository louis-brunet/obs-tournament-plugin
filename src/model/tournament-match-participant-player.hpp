#pragma once

#include "src/model/player-reference.hpp"
#include "src/model/tournament-match-participant.hpp"

class TournamentMatchParticipantPlayer : public TournamentMatchParticipant {
public:
	TournamentMatchParticipantPlayer(PlayerReference _playerReference = PlayerReference());
	// TournamentMatchParticipantPlayer(Player *_player = nullptr);
	// TournamentMatchParticipant(TournamentMatch *deciderMatch);
	~TournamentMatchParticipantPlayer();
    bool isValid() const override;
    bool isReady() const override;
    std::string displayName() const override;
    // inline operator std::string() const { return this->_player->name(); };

    void save(obs_data_t *dataObj) const override;
    void load(obs_data_t *dataObj) override;

private:
    PlayerReference _playerReference;
    // Player *_player;
};
