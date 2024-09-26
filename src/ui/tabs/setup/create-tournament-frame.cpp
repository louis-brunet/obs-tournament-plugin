#include "create-tournament-frame.hpp"
#include "src/data/plugin-data.hpp"
#include "src/data/tournament-reference.hpp"
#include "src/data/tournament.hpp"
#include "src/logger.hpp"
#include "src/ui/components/button.hpp"
#include "src/ui/components/icon.hpp"
#include "src/ui/components/labeled-input.hpp"
#include "src/ui/components/line-edit.hpp"
#include "src/ui/dialogs/error-dialog.hpp"
#include "src/ui/tabs/custom-tournament/custom-tournament-tab.hpp"
#include "src/ui/tabs/setup/create-player-frame.hpp"
#include "src/ui/validation.hpp"
#include <obs-module.h>
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>

using namespace Logger;

CreateTournamentFrame::CreateTournamentFrame()
    : QFrame() // QGroupBox(obs_module_text("setup.createTournament.title"))
{
    auto frameLayout = new QVBoxLayout();
    this->setLayout(frameLayout);

    this->_tournamentTitleLineEdit = new AppLineEdit();
    this->_tournamentTitleLineEdit->setPlaceholderText(
        obs_module_text("setup.createTournament.titleInputPlaceholder"));
    auto tournamentTitleLabeledInput = new AppLabeledInput(
        obs_module_text("setup.createTournament.titleInputLabel"),
        this->_tournamentTitleLineEdit);

    this->_tournamentTypeComboBox = new QComboBox();
    this->_tournamentTypeComboBox->setEditable(true);
    this->_tournamentTypeComboBox->setMaxCount(2);
    this->_tournamentTypeComboBox->addItem("", Tournament::Type::Unknown);
    this->_tournamentTypeComboBox->addItem(
        obs_module_text("tournamentType.custom"), Tournament::Type::Custom);
    auto tournamentTypeLabeledInput = new AppLabeledInput(
        obs_module_text("setup.createTournament.typeInputLabel"),
        this->_tournamentTypeComboBox);

    auto addPlayerButton =
        new AppButton(obs_module_text("setup.createTournament.addPlayerButton"),
                      AppIcon(AppIcon::Type::Add));
    this->connect(addPlayerButton, &QPushButton::clicked,
                  [this]() { this->addPlayer(); });

    auto playerListButtons = new QHBoxLayout();
    playerListButtons->addWidget(addPlayerButton, 0);

    auto playerListWidget = new QGroupBox(
        obs_module_text("setup.createTournament.playerListTitle"));
    auto playerListWrapperLayout = new QVBoxLayout();
    playerListWidget->setLayout(playerListWrapperLayout);
    this->_playerListLayout = new QVBoxLayout();
    playerListWrapperLayout->addLayout(this->_playerListLayout);
    playerListWrapperLayout->addLayout(playerListButtons);

    for (int i = 0; i < 1; i++) {
        this->addPlayer();
    }

    auto endTournamentCreationButton = new AppButton(
        obs_module_text("setup.createTournament.endTournamentCreationButton"));
    this->connect(endTournamentCreationButton, &QPushButton::clicked, [this]() {
        try {
            this->endTournamentCreation();
        } catch (const std::exception &e) {
            Logger::log(LOG_ERROR, "Error during tournament creation: %s",
                        e.what());
            throw e;
        }
    });

    frameLayout->addWidget(tournamentTitleLabeledInput);
    frameLayout->addWidget(tournamentTypeLabeledInput);
    frameLayout->addWidget(playerListWidget);
    frameLayout->addWidget(endTournamentCreationButton);
}

CreateTournamentFrame::~CreateTournamentFrame() {}

bool CreateTournamentFrame::endTournamentCreation()
{
    auto tournamentType =
        (Tournament::Type)this->_tournamentTypeComboBox->currentData().toInt();
    log(LOG_INFO, "Chose tournament type %d", tournamentType);
    if (!Validation::validate(
            tournamentType != Tournament::Type::Unknown, "%s",
            obs_module_text("error.setup.missingTournamentType"))) {
        return false;
    }

    std::string newTournamentTitle =
        this->_tournamentTitleLineEdit->text().toStdString();
    log(LOG_INFO, "Tournament title: '%s'", newTournamentTitle.c_str());
    if (!Validation::validate(
            newTournamentTitle != "", "%s",
            obs_module_text("error.setup.missingTournamentTitle"))) {
        return false;
    }

    std::vector<std::shared_ptr<Player>> players;
    for (int playerIndex = 0; playerIndex < this->_playerListLayout->count();
         playerIndex++) {
        auto newPlayerFrame = static_cast<CreatePlayerFrame *>(
            this->_playerListLayout->itemAt(playerIndex)->widget());

        auto playerName = newPlayerFrame->getPlayerName();
        if (!Validation::validate(
                playerName != "", "Player %d: %s", playerIndex + 1,
                obs_module_text("error.setup.missingPlayerName"))) {
            return false;
        }

        auto playerImagePath = newPlayerFrame->getPlayerImagePath();
        if (!Validation::validate(
                playerImagePath != "", "Player %d: %s", playerIndex + 1,
                obs_module_text("error.setup.missingPlayerImage"))) {
            return false;
        }

        auto playerDescription = newPlayerFrame->getPlayerDescription();
        if (!Validation::validate(
                playerDescription != "", "Player %d: %s", playerIndex + 1,
                obs_module_text("error.setup.missingPlayerDescription"))) {
            return false;
        }

        auto player = std::make_shared<Player>(playerName, playerImagePath,
                                               playerDescription);
        players.push_back(player);
    }
    log(LOG_INFO, "Found %d players", players.size());
    if (!Validation::validate(players.size() != 0, "%s",
                              obs_module_text("error.setup.notEnoughPlayers"))) {
        return false;
    }

    auto tournamentIndex = pluginData->tournaments.size();
    TournamentReference newTournamentReference((long long)tournamentIndex);
    std::shared_ptr<Tournament> newTournament = std::make_shared<Tournament>();
    newTournament->setType(tournamentType);
    newTournament->setPlayers(std::move(players));
    newTournament->setName(newTournamentTitle.c_str());

    this->tournamentCreated(newTournament);

    // auto tournamentIndex = pluginData->tournaments.size();
    // TournamentReference newTournamentReference((long long)tournamentIndex);

    BaseTab *newTab;
    switch (tournamentType) {
    case Tournament::Type::Unknown: {
        auto errorDialog = new ErrorDialog(
            this, obs_module_text("error.setup.missingTournamentType"));
        errorDialog->show();
        return false;
    }

    case Tournament::Type::Custom: {
        newTab = new CustomTournamentTab(newTournamentReference);
        // log("TODO custom tournament tab creation");
        // newTournament = new Tournament
        break;
    }

    default:
        throw std::runtime_error("unhandled enum variant");
    }

    // this->tournamentCreated(newTournament, newTab);
    this->tournamentTabCreated(newTab);
    // newTabTitle = newTournament->title.c_str();
    // this->_tabWidget->addTab(newTab, newTournamentTitle.c_str());
    // this->_tabWidget->setCurrentWidget(newTab);
    //
    // this->showTournamentBuilder(false);
    return true;
}

void CreateTournamentFrame::addPlayer()
{
    auto newPlayer = new CreatePlayerFrame();
    this->_playerListLayout->addWidget(newPlayer, 0);
}
