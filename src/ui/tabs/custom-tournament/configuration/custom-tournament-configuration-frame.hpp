#pragma once

#include "src/data/tournament.hpp"
#include <QFrame>
#include <QBoxLayout>

class CustomTournamentConfigurationFrame : public QFrame {
public:
	CustomTournamentConfigurationFrame(
		std::shared_ptr<Tournament> tournament);
	~CustomTournamentConfigurationFrame();

private:
	std::shared_ptr<Tournament> _tournament;
	QVBoxLayout *_roundListLayout;

	void addNewRound();
	void addExistingRound(std::shared_ptr<TournamentRound> round);
};
