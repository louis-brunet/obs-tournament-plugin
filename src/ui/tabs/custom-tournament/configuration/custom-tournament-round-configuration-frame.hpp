#pragma once

#include "src/data/tournament-round.hpp"
#include <QFrame>
#include <QBoxLayout>

class CustomTournamentRoundConfigurationFrame : public QFrame {
public:
	CustomTournamentRoundConfigurationFrame(
		std::shared_ptr<TournamentRound> tournamentRound);
	~CustomTournamentRoundConfigurationFrame();

private:
	std::shared_ptr<TournamentRound> _tournamentRound;
	QVBoxLayout *_matchListLayout;

	void addNewMatch();
	void addExistingMatch(std::shared_ptr<Match> match);
    void duplicateRound();
    void deleteRound();
};
