#include "setup-tab.hpp"
#include "obs-module.h"
#include "src/model/custom-knockout-tournament.hpp"
#include "src/model/plugin-data.hpp"
#include "src/plugin-support.h"
#include "src/ui/components/line-edit.hpp"
#include "src/ui/dialogs/error-dialog.hpp"
#include "src/ui/tabs/custom-knockout-tab/custom-knockout-tab.hpp"
#include "src/ui/tabs/debug-frame.hpp"

#include <QByteArray>
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QList>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QStringList>
#include <stdexcept>

using namespace std;

class SetupTabNewPlayerFrame : public QFrame {
public:
	SetupTabNewPlayerFrame(uint16_t seed);
	~SetupTabNewPlayerFrame();
	string getPlayerName();

private:
	QLineEdit *playerNameEditText;
};

SetupTabNewPlayerFrame::SetupTabNewPlayerFrame(uint16_t seed)
{

	auto labelText = "Seed " + std::to_string(seed);
	auto *playerNameLabel = new QLabel(labelText.c_str());
	this->playerNameEditText = new AppLineEdit();
	this->playerNameEditText->setPlaceholderText(
		obs_module_text("SetupTabPlayerNameInputPlaceholder"));

	auto *newPlayerLayout = new QHBoxLayout();
	newPlayerLayout->addWidget(playerNameLabel);
	newPlayerLayout->addWidget(this->playerNameEditText);

	this->setLayout(newPlayerLayout);
}

SetupTabNewPlayerFrame::~SetupTabNewPlayerFrame() {}

string SetupTabNewPlayerFrame::getPlayerName()
{
	return this->playerNameEditText->text().toStdString();
}

SetupTabFrame::SetupTabFrame(QTabWidget *_tabWidget)
{
	this->tabWidget = _tabWidget;
	this->playerCount = 0;
	// this->tournamentBuilder = nullptr;
	// this->tournamentBuilder = new TournamentBuilder();

	// auto *setupTabTitle = new QLabel(obs_module_text("SetupTabTitle"));

	this->showTournamentBuilderButton = new QPushButton(
		obs_module_text("SetupTabCreateNewTournamentButton"));
	auto showTournamentBuilderCallback = [this]() {
		this->showTournamentBuilder(true);
	};
	this->connect(this->showTournamentBuilderButton, &QPushButton::clicked,
		      showTournamentBuilderCallback);

	this->finishTournamentBuilderButton = new QPushButton(
		obs_module_text("SetupTabFinishTournamentBuilderButton"));
	this->finishTournamentBuilderButton->setVisible(false);
	auto finishTournamentBuilderCallback = [this]() {
		this->finishTournamentBuilder();
	};
	this->connect(this->finishTournamentBuilderButton,
		      &QPushButton::clicked, finishTournamentBuilderCallback);

	this->initTournamentBuilder();

    // obs_log(LOG_INFO, "before DebugFrame");
    auto onResetDataCallback = [this]() {
        for (auto tabIndex = 1; tabIndex < this->tabWidget->count(); tabIndex++) {
            this->tabWidget->removeTab(tabIndex);
        }
    };
    auto debugFrame = new DebugFrame(onResetDataCallback);
    // obs_log(LOG_INFO, "after DebugFrame");

	// setupTabTitle->setBaseSize
	auto *contentFrame = new QFrame();
	auto *contentLayout = new QVBoxLayout();
	contentLayout->setAlignment(Qt::AlignTop);
	// contentLayout->addWidget(setupTabTitle, 0, Qt::AlignTop);
	contentLayout->addWidget(this->tournamentBuilderFrame);
	contentLayout->addWidget(this->showTournamentBuilderButton);
	contentLayout->addWidget(this->finishTournamentBuilderButton);
    contentLayout->addWidget(debugFrame);
	contentFrame->setLayout(contentLayout);

	auto *contentScrollArea = new QScrollArea();
	contentScrollArea->setWidget(contentFrame);
	contentScrollArea->setWidgetResizable(true);

	auto *setupTabLayout = new QVBoxLayout();
	setupTabLayout->addWidget(contentScrollArea);

	this->setLayout(setupTabLayout);
}

SetupTabFrame::~SetupTabFrame() {}

void SetupTabFrame::initTournamentBuilder()
{
	const map<string, Tournament::Type> tournamentTypeNameToTournamentTypeMap = {
		{obs_module_text("TournamentTypeSingleEliminationKnockout"),
		 Tournament::Type::SingleEliminationKnockoutTournamentType},
		{obs_module_text("TournamentTypeCustomKnockout"),
		 Tournament::Type::CustomKnockoutTournamentType},
	};

	// auto *tournamentBuilderTitle =
	// 	new QLabel(obs_module_text("SetupTabTournamentBuilderTitle"));

	this->tournamentTypeComboBox = new QComboBox();
	for (auto a : tournamentTypeNameToTournamentTypeMap) {
		auto name = a.first;
		auto tournamentType = a.second;
		this->tournamentTypeComboBox->addItem(name.c_str(),
						      (int)tournamentType);
	}

	auto *playerListTitle =
		new QLabel(obs_module_text("SetupTabPlayerListTitle"));

	this->playerListLayout = new QVBoxLayout();

	auto *addPlayerButton =
		new QPushButton(obs_module_text("SetupTabAddPlayerButton"));
	this->connect(addPlayerButton, &QPushButton::clicked,
		      [this]() { this->addNewPlayerFrame(); });

	this->removePlayerButton =
		new QPushButton(obs_module_text("SetupTabRemovePlayerButton"));
	this->connect(this->removePlayerButton, &QPushButton::clicked,
		      [this]() { this->removeNewPlayerFrame(); });

	auto *playerListButtonsLayout = new QHBoxLayout();
	playerListButtonsLayout->addWidget(this->removePlayerButton);
	playerListButtonsLayout->addWidget(addPlayerButton);

	auto *tournamentBuilderLayout = new QVBoxLayout();
	// tournamentBuilderLayout->addWidget(tournamentBuilderTitle, 0,
					   // Qt::AlignTop);
	tournamentBuilderLayout->addWidget(this->tournamentTypeComboBox, 0,
					   Qt::AlignTop);
	tournamentBuilderLayout->addLayout(playerListButtonsLayout);
	tournamentBuilderLayout->addWidget(playerListTitle);
	tournamentBuilderLayout->addLayout(this->playerListLayout);

	this->tournamentBuilderFrame = new QGroupBox(obs_module_text("SetupTabTournamentBuilderTitle"));
	this->tournamentBuilderFrame->setLayout(tournamentBuilderLayout);
	this->tournamentBuilderFrame->setVisible(false);

	this->addNewPlayerFrame();
	this->addNewPlayerFrame();
}

void SetupTabFrame::showTournamentBuilder(bool isVisible)
{
	this->showTournamentBuilderButton->setVisible(!isVisible);
	this->finishTournamentBuilderButton->setVisible(isVisible);
	this->tournamentBuilderFrame->setVisible(isVisible);
}

void SetupTabFrame::addNewPlayerFrame()
{
	this->playerCount++;
	auto *newPlayerFrame = new SetupTabNewPlayerFrame(this->playerCount);
	this->playerListLayout->addWidget(newPlayerFrame, 0, Qt::AlignTop);
	this->updateRemovePlayerButtonVisibility();
}

void SetupTabFrame::removeNewPlayerFrame()
{
	if (this->playerCount > 0) {
		auto lastIndex = this->playerCount - 1;
		// auto lastIndex = this->playerListLayout->count() - 1;
		auto *lastChild = this->playerListLayout->takeAt(lastIndex);
		delete lastChild->widget();
		delete lastChild;

		this->playerCount--;
		this->updateRemovePlayerButtonVisibility();
	}
}

void SetupTabFrame::updateRemovePlayerButtonVisibility()
{
	this->removePlayerButton->setVisible(this->playerCount > 0);
}

bool SetupTabFrame::finishTournamentBuilder()
{
	auto tournamentType =
		(Tournament::Type)this->tournamentTypeComboBox->currentData()
			.toInt();
	obs_log(LOG_INFO, "Chose tournament type %d", tournamentType);

	// auto players = this->getPlayersFromPlayerList();
	vector<Player *> players;

	for (int playerIndex = 0; playerIndex < this->playerListLayout->count();
	     playerIndex++) {
		auto newPlayerFrame = reinterpret_cast<SetupTabNewPlayerFrame *>(
			this->playerListLayout->itemAt(playerIndex)->widget());
		auto playerName = newPlayerFrame->getPlayerName();

		if (playerName == "") {
			const unsigned int errorMessageBufferSize = 256;
			char errorMessage[errorMessageBufferSize];
			snprintf(errorMessage, errorMessageBufferSize,
				 "Seed %d: %s", playerIndex + 1,
				 obs_module_text("ErrorMissingPlayerName"));
			auto errorDialog = new ErrorDialog(this, errorMessage);
			errorDialog->show();
			return false;
		}

		// Player player(playerName);
		auto player = new Player(playerName);
		players.push_back(player);
	}
	obs_log(LOG_INFO, "Found %d players", players.size());

	Tournament *newTournament;
	QWidget *newTab;
	const char *newTabTitle;

	switch (tournamentType) {
	case Tournament::Type::SingleEliminationKnockoutTournamentType:
		// TODO: get tournament config, create new tournament tab
		throw std::runtime_error("todo");
		break;
	case Tournament::Type::CustomKnockoutTournamentType:
		obs_log(LOG_INFO,
			"[finishTournamentBuilder] Creating custom knockout tab");
		newTournament = new CustomKnockoutTournament(players);
		newTab = new CustomKnockoutTabFrame(reinterpret_cast<CustomKnockoutTournament *>(newTournament));
		newTabTitle = obs_module_text("CustomKnockoutTabTitle");
		break;
		// default:
		// 	throw std::runtime_error("unhandled enum variant");
	}
	pluginData->tournaments.push_back(newTournament);
	this->tabWidget->addTab(newTab, newTabTitle);
	this->tabWidget->setCurrentWidget(newTab);

	this->showTournamentBuilder(false);
	return true;
}
