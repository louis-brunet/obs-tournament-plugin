#include "custom-tournament-round-configuration-frame.hpp"
#include "src/logger.hpp"
#include "src/ui/components/icon.hpp"
#include "src/ui/components/labeled-input.hpp"
#include "src/ui/components/line-edit.hpp"
#include "src/ui/tabs/custom-tournament/configuration/custom-tournament-match-configuration-frame.hpp"
#include <obs-module.h>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPushButton>

CustomTournamentRoundConfigurationFrame::CustomTournamentRoundConfigurationFrame(
	std::shared_ptr<TournamentRound> tournamentRound)
	: _tournamentRound(tournamentRound)
{
	auto roundNameLineEdit = new AppLineEdit();
	roundNameLineEdit->setPlaceholderText(obs_module_text(
		"customTournament.configuration.roundNameInputPlaceholder"));
	auto roundNameInput = new AppLabeledInput(
		obs_module_text(
			"customTournament.configuration.roundNameInputLabel"),
		roundNameLineEdit);

    auto duplicateRoundButton = new QPushButton(AppIcon(AppIcon::Type::Copy), "");
    duplicateRoundButton->setToolTip(obs_module_text("customTournament.configuration.duplicateRoundButtonTooltip"));
	this->connect(duplicateRoundButton, &QPushButton::clicked,
		      [this]() { this->duplicateRound(); });

    auto deleteRoundButton = new QPushButton(AppIcon(AppIcon::Type::Delete), "");
    deleteRoundButton->setToolTip(obs_module_text("customTournament.configuration.deleteRoundButtonTooltip"));
	this->connect(deleteRoundButton, &QPushButton::clicked,
		      [this]() { this->deleteRound(); });

    auto roundConfigLayout = new QHBoxLayout();
    roundConfigLayout->addWidget(roundNameInput, 1);
    roundConfigLayout->addWidget(duplicateRoundButton, 0);
    roundConfigLayout->addWidget(deleteRoundButton, 0);
	this->_matchListLayout = new QVBoxLayout();

	// this->_matchListLayout->addWidget(new QLabel("TODO round config"));

	auto addMatchButton = new QPushButton(obs_module_text(
		"customTournament.configuration.addMatchButton"));
	this->connect(addMatchButton, &QPushButton::clicked,
		      [this]() { this->addNewMatch(); });

	auto tournamentMatches = this->_tournamentRound->matches();
	if (tournamentMatches.size() > 0) {
		for (auto match : tournamentMatches) {
			this->addExistingMatch(match);
		}
	} else {
		this->addNewMatch();
	}

	auto frameLayout = new QVBoxLayout();
    frameLayout->addLayout(roundConfigLayout, 0);
	frameLayout->addLayout(this->_matchListLayout, 1);
	frameLayout->addWidget(addMatchButton, 0);

	this->setLayout(frameLayout);
}

CustomTournamentRoundConfigurationFrame::
	~CustomTournamentRoundConfigurationFrame()
{
}

void CustomTournamentRoundConfigurationFrame::addNewMatch()
{
	auto newMatch = std::make_shared<Match>();
	this->_tournamentRound->matches().push_back(newMatch);

	this->addExistingMatch(newMatch);
}

void CustomTournamentRoundConfigurationFrame::addExistingMatch(
	std::shared_ptr<Match> match)
{
	auto newMatchConfigurationFrame =
		new CustomTournamentMatchConfigurationFrame(match);
	this->_matchListLayout->addWidget(newMatchConfigurationFrame);
}

void CustomTournamentRoundConfigurationFrame::duplicateRound() {
    Logger::log("[CustomTournamentRoundConfigurationFrame::duplicateRound()] TODO");
}

void CustomTournamentRoundConfigurationFrame::deleteRound() {
    Logger::log("[CustomTournamentRoundConfigurationFrame::deleteRound()] TODO");
}
