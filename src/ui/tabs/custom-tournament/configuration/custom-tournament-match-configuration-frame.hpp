#pragma once

#include "src/data/match.hpp"
#include <QFrame>
#include <QBoxLayout>

class CustomTournamentMatchConfigurationFrame : public QFrame {
public:
	CustomTournamentMatchConfigurationFrame(
		std::shared_ptr<Match> match);
	~CustomTournamentMatchConfigurationFrame();

private:
	std::shared_ptr<Match> _match;
    void duplicateMatch();
    void deleteMatch();
};
