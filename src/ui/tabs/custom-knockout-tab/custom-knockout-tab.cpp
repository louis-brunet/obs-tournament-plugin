#include "custom-knockout-tab.hpp"
#include "src/model/tournament-match-participant.hpp"
#include "src/ui/dialogs/error-dialog.hpp"

#include <cstdio>
#include <obs-module.h>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>

using namespace std;

CustomKnockoutTabFrame::CustomKnockoutTabFrame(
	CustomKnockoutTournament *tournament)
	: _tournament(tournament)
// : CustomKnockoutTabFrame(tournament->players)
{
	// TODO: instead of calling players constructor, need ustom logic to restore running tournamnent
	// obs_log(LOG_INFO, "CustomKnockoutTabFrame::CustomKnockoutTabFrame called for tournament");

	// auto __players = tournament->players;

	// obs_log(LOG_INFO, "CustomKnockoutTabFrame::CustomKnockoutTabFrame called for players");
	// this->players = _players;
	auto *contentLayout = new QVBoxLayout();

	// auto tabTitle =
	// 	new QLabel(obs_module_text("TournamentTypeCustomKnockout"));
	// contentLayout->addWidget(tabTitle);

    // TournamentReference tournamentReference(tournamentIndex);
	this->matchConfigurationFrame =
		new CustomKnockoutMatchConfigurationFrame(tournament);
	contentLayout->addWidget(matchConfigurationFrame);

	this->endMatchConfigurationButton = new QPushButton(
		obs_module_text("CustomKnockoutEndMatchConfigurationButton"));
	contentLayout->addWidget(endMatchConfigurationButton);
	this->connect(endMatchConfigurationButton, &QPushButton::clicked,
		      [this]() { this->endTournamentConfiguration(); });
	// obs_log(LOG_INFO, "[CustomKnockoutTabFrame] Creating knockout content");
	// this->initKnockoutContent(contentLayout);

	this->tournamentRunningWidget = new CustomKnockoutRunningFrame();
	this->tournamentRunningWidget->setVisible(false);
	contentLayout->addWidget(this->tournamentRunningWidget);

	auto *contentFrame = new QFrame();
	contentFrame->setLayout(contentLayout);

	auto *contentScrollArea = new QScrollArea();
	contentScrollArea->setWidget(contentFrame);
	contentScrollArea->setWidgetResizable(true);

	auto tabLayout = new QVBoxLayout();
	tabLayout->addWidget(contentScrollArea);
	this->setLayout(tabLayout);

	if (this->_tournament->isStarted()) {
        // this->endMatchConfigurationButton->click();
        this->endTournamentConfiguration();
	}
}

// CustomKnockoutTabFrame::CustomKnockoutTabFrame(std::vector<Player *> __players)
// {
// }

CustomKnockoutTabFrame::~CustomKnockoutTabFrame() {}

bool CustomKnockoutTabFrame::endTournamentConfiguration()
{
	// auto tournamentMatches = this->_tournament->matches;
	// this->matchConfigurationFrame->getTournamentMatches();
	const auto errorBufferSize = 256;
	char errorMessage[errorBufferSize];

	if (this->_tournament->matches.size() == 0) {
		snprintf(
			errorMessage, errorBufferSize, "%s",
			obs_module_text("ErrorCustomKnockoutNotEnoughMatches"));
		auto errorDialog = new ErrorDialog(this, errorMessage);
		errorDialog->show();
		return false;
	}

	// Validate tournament matches
	for (auto iTournamentMatch : this->_tournament->matches) {
		// for (unsigned int matchIndex = 0; matchIndex < tournamentMatches.size();
		//      matchIndex++) {
		// 	auto iTournamentMatch = tournamentMatches[matchIndex];

		if (!iTournamentMatch->participant1()->isValid()) {
			snprintf(
				errorMessage, errorBufferSize,
				"%s %s, %s 1 - %s", obs_module_text("Match"),
				iTournamentMatch->matchLabel().c_str(),
				obs_module_text("Player"),
				obs_module_text(
					"ErrorCustomKnockoutInvalidMatchParticipant"));
			// auto errorMessage = obs_module_text("Match");
			auto errorDialog = new ErrorDialog(this, errorMessage);
			errorDialog->show();
			return false;
		}
		if (!iTournamentMatch->participant2()->isValid()) {
			snprintf(
				errorMessage, errorBufferSize,
				"%s %s, %s 2 - %s", obs_module_text("Match"),
				iTournamentMatch->matchLabel().c_str(),
				obs_module_text("Player"),
				obs_module_text(
					"ErrorCustomKnockoutInvalidMatchParticipant"));
			// auto errorMessage = obs_module_text("Match");
			auto errorDialog = new ErrorDialog(this, errorMessage);
			errorDialog->show();
			return false;
		}
	}

	this->matchConfigurationFrame->setVisible(false);
	this->endMatchConfigurationButton->setVisible(false);

	// this->matchConfigurationFrame->setContentsMargins(0,0,0,0);
	this->tournamentRunningWidget->setMatches(this->_tournament->matches);
	this->tournamentRunningWidget->setVisible(true);
	// (new QVBoxLayout()) ->(true);

    this->_tournament->start();
	return true;
}

// void CustomKnockoutTabFrame::initKnockoutContent(QVBoxLayout *layout)
// {
// 	auto columnLayout = new QGridLayout();
// 	this->matchListLayout = new QVBoxLayout();
// 	columnLayout->addLayout(this->matchListLayout, 0, 0);
//
// 	auto ongoingMatchesColumn = new QVBoxLayout();
// 	columnLayout->addLayout(ongoingMatchesColumn, 0, 1);
// 	ongoingMatchesColumn->addWidget(
// 		new QLabel(obs_module_text("OngoingMatchesTitle")));
//
// 	this->ongoingMatchListLayout = new QVBoxLayout();
// 	ongoingMatchesColumn->addLayout(this->ongoingMatchListLayout);
//
// 	auto buttonLayout = new QHBoxLayout();
// 	buttonLayout->setAlignment(Qt::AlignRight);
//
// 	auto removeMatchButton = new QPushButton(
// 		obs_module_text("CustomKnockoutTabRemoveMatchButton"));
// 	buttonLayout->addWidget(removeMatchButton);
// 	this->connect(removeMatchButton, &QPushButton::clicked, [this]() {
// 		this->removeMatch();
// 		this->updateAllPlayerOptions();
// 	});
//
// 	auto addMatchButton = new QPushButton(
// 		obs_module_text("CustomKnockoutTabAddMatchButton"));
// 	buttonLayout->addWidget(addMatchButton);
// 	this->connect(addMatchButton, &QPushButton::clicked, [this]() {
// 		this->addMatch();
// 		this->updateAllPlayerOptions();
// 	});
//
// 	obs_log(LOG_INFO,
// 		"[CustomKnockoutTabFrame::initKnockoutContent] Adding knockout matches");
// 	for (int i = 0; i < 2; i++) {
// 		this->addMatch();
// 	}
// 	obs_log(LOG_INFO,
// 		"[CustomKnockoutTabFrame::initKnockoutContent] Updating player options");
// 	this->updateAllPlayerOptions();
//
// 	layout->addLayout(columnLayout);
// 	layout->addLayout(buttonLayout);
// }
