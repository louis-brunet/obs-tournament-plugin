#include "custom-knockout-running-frame.hpp"

#include <QGridLayout>
#include <QLabel>

CustomKnockoutRunningFrame::CustomKnockoutRunningFrame()
{
	auto frameLayout = new QGridLayout();
	frameLayout->setColumnStretch(0, 9);
	frameLayout->setColumnStretch(1, 3);

	this->allMatchesWidget = new CustomKnockoutRunningAllMatchesFrame();
	frameLayout->addWidget(allMatchesWidget, 0, 0);

	// TODO: tournament running frame
	// auto ongoingMatchesWidget = new CustomKnockoutRunningOngoingMatchesFrame();
	// frameLayout->addWidget(ongoingMatchesWidget, 0, 1);

	this->setLayout(frameLayout);
}

CustomKnockoutRunningFrame::~CustomKnockoutRunningFrame() {}

void CustomKnockoutRunningFrame::setMatches(
	std::vector<TournamentMatch *> matches)
{
    this->allMatchesWidget->setMatches(matches);
    // TODO: ongoing matches
}
