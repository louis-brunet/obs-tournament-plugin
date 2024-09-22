#include "custom-tournament-configuration-frame.hpp"
#include "src/data/tournament-round.hpp"
#include "src/ui/tabs/custom-tournament/configuration/custom-tournament-round-configuration-frame.hpp"
#include <QBoxLayout>
#include <obs-module.h>
#include <qpushbutton.h>

CustomTournamentConfigurationFrame::CustomTournamentConfigurationFrame(
	std::shared_ptr<Tournament> tournament)
	: _tournament(tournament)
{
	this->_roundListLayout = new QVBoxLayout();
	// for (auto round : tournament)
	// addRound

	auto addRoundButton = new QPushButton(obs_module_text(
		"customTournament.configuration.addRoundButton"));
	this->connect(addRoundButton, &QPushButton::clicked,
		      [this]() { this->addNewRound(); });

	auto tournamentRounds = this->_tournament->rounds();
	if (tournamentRounds.size() > 0) {
		for (auto round : tournamentRounds) {
			this->addExistingRound(round);
		}
	} else {
		this->addNewRound();
	}

	auto frameLayout = new QVBoxLayout();
	frameLayout->addLayout(this->_roundListLayout);
	frameLayout->addWidget(addRoundButton);

	this->setLayout(frameLayout);
}

CustomTournamentConfigurationFrame::~CustomTournamentConfigurationFrame() {}

void CustomTournamentConfigurationFrame::addNewRound()
{
	auto newRound = std::make_shared<TournamentRound>();
	this->_tournament->rounds().push_back(newRound);

	this->addExistingRound(newRound);
}

void CustomTournamentConfigurationFrame::addExistingRound(
	std::shared_ptr<TournamentRound> round)
{
	auto newRoundConfigurationFrame =
		new CustomTournamentRoundConfigurationFrame(round);
	this->_roundListLayout->addWidget(newRoundConfigurationFrame);
}
