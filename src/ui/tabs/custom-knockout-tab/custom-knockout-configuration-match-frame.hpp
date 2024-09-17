#pragma once

#include "src/model/tournament-match.hpp"
#include "src/ui/components/player-combo-box.hpp"

#include <QFrame>

class CustomKnockoutMatchFrame : public QFrame {
public:
	CustomKnockoutMatchFrame(TournamentMatch *tournamentMatch);
	~CustomKnockoutMatchFrame();
	PlayerComboBox *player1ComboBox();
	PlayerComboBox *player2ComboBox();
	TournamentMatch *createTournamentMatch();

private:
	PlayerComboBox *_player1ComboBox;
	PlayerComboBox *_player2ComboBox;
	// std::string matchLabel;
    TournamentMatch *_tournamentMatch;
};
