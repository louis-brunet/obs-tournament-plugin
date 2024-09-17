#include "custom-knockout-running-all-matches-frame.hpp"

#include <QLabel>
#include <vector>

CustomKnockoutRunningAllMatchesFrame::CustomKnockoutRunningAllMatchesFrame()
{
	auto frameLayout = new QVBoxLayout();

	// TODO: tournament running all matches frame
	this->matchListLayout = frameLayout;
	// frameLayout->addWidget(new QLabel("TODO: all matches"), 1);

	this->setLayout(frameLayout);
}

CustomKnockoutRunningAllMatchesFrame::~CustomKnockoutRunningAllMatchesFrame() {}

void CustomKnockoutRunningAllMatchesFrame::setMatches(
	std::vector<TournamentMatch *> matches)
{
	for (auto iTournamentMatch : matches) {
		this->matchListLayout->addWidget(
			new QLabel(QString::fromStdString(
				(std::string) "TODO: match " +
				iTournamentMatch->matchLabel())), 0);
	}
}
