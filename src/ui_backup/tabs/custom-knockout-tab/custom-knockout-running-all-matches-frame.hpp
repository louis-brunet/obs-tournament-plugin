#pragma once

#include "src/model/tournament-match.hpp"
#include <QFrame>
#include <QBoxLayout>

class CustomKnockoutRunningAllMatchesFrame : public QFrame {
public:
	CustomKnockoutRunningAllMatchesFrame();
	~CustomKnockoutRunningAllMatchesFrame();
	void setMatches(std::vector<TournamentMatch *> matches);

private:
    QBoxLayout *matchListLayout;
};
