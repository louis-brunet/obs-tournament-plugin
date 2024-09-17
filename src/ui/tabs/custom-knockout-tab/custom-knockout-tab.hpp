#pragma once

#include "src/model/custom-knockout-tournament.hpp"
#include "src/ui/tabs/custom-knockout-tab/custom-knockout-configuration-frame.hpp"
#include "src/ui/tabs/custom-knockout-tab/custom-knockout-running-frame.hpp"
#include <QFrame>
#include <QPushButton>

class CustomKnockoutTabFrame : public QFrame {
	Q_OBJECT;

public:
	// CustomKnockoutTabFrame(std::vector<Player *> players);
	CustomKnockoutTabFrame(CustomKnockoutTournament *tournament);
	CustomKnockoutTabFrame();
	~CustomKnockoutTabFrame();

private:
    const Tournament *_tournament;
	// QBoxLayout *ongoingMatchListLayout;
    CustomKnockoutRunningFrame *tournamentRunningWidget;
    // QLayout *tournamentRunningLayout;
    QPushButton *endMatchConfigurationButton;
    CustomKnockoutMatchConfigurationFrame *matchConfigurationFrame;
    // vector<CustomKnockoutMatchFrame *> matchFrames;

	void initKnockoutContent(QVBoxLayout *layout);
    bool endTournamentConfiguration();
};
