#include "custom-knockout-configuration-frame.hpp"
#include "src/plugin-support.h"
#include "src/model/tournament-match.hpp"
#include "src/ui/tabs/custom-knockout-tab/custom-knockout-configuration-match-frame.hpp"

#include <obs-module.h>
#include <QPushButton>
#include <QCompleter>

using namespace std;

CustomKnockoutMatchConfigurationFrame::CustomKnockoutMatchConfigurationFrame(
	CustomKnockoutTournament *tournament)
	: _tournament(tournament)
{

	// auto matches = tournament->matches();

	// this->players = tournament->players;
	// this->totalMatchCount = (uint32_t)matches.size();

	auto buttonLayout = new QHBoxLayout();
	// buttonLayout->setAlignment(Qt::AlignRight);

	auto removeMatchButton = new QPushButton(
		obs_module_text("CustomKnockoutTabRemoveMatchButton"));
	buttonLayout->addWidget(removeMatchButton, 1);
	this->connect(removeMatchButton, &QPushButton::clicked, [this]() {
		this->removeMatch();
		this->updateAllPlayerOptions();
	});

	auto addMatchButton = new QPushButton(
		obs_module_text("CustomKnockoutTabAddMatchButton"));
	buttonLayout->addWidget(addMatchButton, 1);
	this->connect(addMatchButton, &QPushButton::clicked, [this]() {
		// auto matchIndex = (uint32_t)this->_tournament->matches.size();
		// auto matchLabel = this->getMatchIdFromMatchIndex(matchIndex);
		this->addMatch();
		this->updateAllPlayerOptions();
	});

	this->matchListLayout = new QVBoxLayout();
	this->matchListLayout->setAlignment(Qt::AlignTop);

	obs_log(LOG_INFO,
		"[CustomKnockoutTabFrame::initKnockoutContent] Adding knockout matches, _tournament->matches.size()=%d",
		_tournament->matches.size());

	auto matchCount = (uint32_t)this->_tournament->matches.size();
	if (matchCount > 0) {
		for (auto tournamentMatch : this->_tournament->matches) {
			this->addMatch(tournamentMatch);
			// this->addMatch(m->matchLabel(), m->participant1(),
			// 	       m->participant2());
		}
	} else {
		for (int i = 0; i < 2; i++) {
			this->addMatch();
			// auto matchLabel = this->getMatchIdFromMatchIndex(
			// 	(uint32_t)this->_tournament->matches.size());
			// this->addMatch(matchLabel);
		}
	}

	obs_log(LOG_INFO,
		"[CustomKnockoutTabFrame::initKnockoutContent] Updating player options");
	this->updateAllPlayerOptions();

	auto frameLayout = new QVBoxLayout();
	// frameLayout->setSpacing(0);
	frameLayout->setAlignment(Qt::AlignTop);
	frameLayout->addLayout(this->matchListLayout, 1);
	frameLayout->addLayout(buttonLayout);

	this->setLayout(frameLayout);
}

CustomKnockoutMatchConfigurationFrame::~CustomKnockoutMatchConfigurationFrame()
{
}

void CustomKnockoutMatchConfigurationFrame::addMatch(
	TournamentMatch *tournamentMatch)
{
	TournamentMatchParticipant *participant1 = nullptr;
	TournamentMatchParticipant *participant2 = nullptr;

	if (!tournamentMatch) {
		auto matchLabel = this->getMatchIdFromMatchIndex(
			(uint32_t)this->_tournament->matches.size());
		tournamentMatch = new TournamentMatch(matchLabel.c_str());
		this->_tournament->matches.push_back(tournamentMatch);
	} else {
		participant1 = tournamentMatch->participant1();
		participant2 = tournamentMatch->participant2();
	}

	auto newMatchFrame = new CustomKnockoutMatchFrame(tournamentMatch);

	if (participant1) {
		auto comboBox = newMatchFrame->player1ComboBox();
		comboBox->setPlayerOptions(this->_tournament->players, {});
		auto comboBoxCompleter = comboBox->completer();
		auto matchFlags = comboBoxCompleter->filterMode();
		auto participantIndex = comboBox->findText(
			QString::fromStdString(participant1->displayName()),
			matchFlags);
		comboBox->setCurrentIndex(participantIndex);
	}
	if (participant2) {
		auto comboBox = newMatchFrame->player2ComboBox();
		comboBox->setPlayerOptions(this->_tournament->players, {});
		auto comboBoxCompleter = comboBox->completer();
		auto matchFlags = comboBoxCompleter->filterMode();
		auto participantIndex = comboBox->findText(
			QString::fromStdString(participant2->displayName()),
			matchFlags);
		comboBox->setCurrentIndex(participantIndex);
	}

	this->matchListLayout->addWidget(newMatchFrame, 0);
}

void CustomKnockoutMatchConfigurationFrame::removeMatch()
{
	auto matches = this->_tournament->matches;
	auto matchCount = (uint32_t)matches.size();
	if (matchCount > 0) {
		auto lastIndex = matchCount - 1;
		auto layoutItem = this->matchListLayout->takeAt((int)lastIndex);

		delete layoutItem->widget();
		delete layoutItem;

		auto lastTournamentMatch = matches.at(lastIndex);
		matches.pop_back();
		delete lastTournamentMatch;
	}
}

// // FIXME: should not need this method, plugin data should ideally stay updated
// std::vector<TournamentMatch *>
// CustomKnockoutMatchConfigurationFrame::getTournamentMatches()
// {
// 	std::vector<TournamentMatch *> matches;
//
// 	for (int matchIndex = 0; matchIndex < this->matchListLayout->count();
// 	     matchIndex++) {
// 		// auto tournamentMatch = new TournamentMatch(player1, player2);
// 		auto matchFrame = reinterpret_cast<CustomKnockoutMatchFrame *>(
// 			this->matchListLayout->itemAt(matchIndex)->widget());
// 		obs_log(LOG_DEBUG,
// 			"[CustomKnockoutMatchConfigurationFrame::updateAllPlayerOptions] match %d - creating tournament match",
// 			matchIndex);
// 		auto tournamentMatch = matchFrame->createTournamentMatch();
// 		matches.push_back(tournamentMatch);
// 	}
//
// 	return matches;
// }

void CustomKnockoutMatchConfigurationFrame::updateAllPlayerOptions()
{
	// auto matches = this->_tournament->matches;
	// Retrieve all match configurations
	// auto matches = this->getTournamentMatches();
	// auto players = this->_tournament->players;

	// Update all player selection combo boxes
	for (int matchIndex = 0; matchIndex < this->matchListLayout->count();
	     matchIndex++) {
		obs_log(LOG_INFO,
			"[CustomKnockoutMatchConfigurationFrame::updateAllPlayerOptions] match %d",
			matchIndex);
		// auto tournamentMatch = new TournamentMatch(player1, player2);
		auto matchFrame = reinterpret_cast<CustomKnockoutMatchFrame *>(
			this->matchListLayout->itemAt(matchIndex)->widget());
		matchFrame->player1ComboBox()->setPlayerOptions(
			this->_tournament->players, this->_tournament->matches);
		matchFrame->player2ComboBox()->setPlayerOptions(
			this->_tournament->players, this->_tournament->matches);
	}
}

std::string CustomKnockoutMatchConfigurationFrame::getMatchIdFromMatchIndex(
	uint32_t matchIndex)
{
	std::string matchIdResult = "";
	int64_t tempMatchIndex = matchIndex;

	// matchIdResult += (char) (((uint16_t) 'A') + (matchIndex % 26));
	// matchIndex = (matchIndex / 26) - 1;

	while (tempMatchIndex >= 0) {
		matchIdResult = (char)(((int32_t)'A') + (tempMatchIndex % 26)) +
				matchIdResult;
		tempMatchIndex = (tempMatchIndex / 26) - 1;
	};

	return matchIdResult;
}
