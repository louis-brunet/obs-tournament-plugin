#include "custom-tournament-match-configuration-frame.hpp"
#include "src/data/tournament.hpp"
#include "src/logger.hpp"
#include "src/ui/components/icon.hpp"
#include "src/ui/tabs/custom-tournament/configuration/match-participant-input.hpp"
#include <memory>
#include <obs-module.h>
#include <QLabel>
#include <QPushButton>

CustomTournamentMatchConfigurationFrame::CustomTournamentMatchConfigurationFrame(
    std::shared_ptr<Match> match, MatchReference matchReference)
    : _match(match)
{
    Logger::log(LOG_DEBUG,
                "[CustomTournamentMatchConfigurationFrame] constructor called");

    auto matchLabelText = matchReference.toMatchLabel();
    this->participant1Input = new MatchParticipantInput();
    //TODO: when to initialize available players and matches ?
    this->connect(this->participant1Input,
                  &MatchParticipantInput::participantChanged,
                  [this](auto newParticipant) {
                      this->_match->setParticipant1(newParticipant);
                  });

    this->participant2Input = new MatchParticipantInput();
    this->connect(this->participant2Input,
                  &MatchParticipantInput::participantChanged,
                  [this](auto newParticipant) {
                      this->_match->setParticipant2(newParticipant);
                  });

    auto duplicateMatchButton =
        new QPushButton(AppIcon(AppIcon::Type::Copy), "");
    duplicateMatchButton->setToolTip(obs_module_text(
        "customTournament.configuration.duplicateMatchButtonTooltip"));
    this->connect(duplicateMatchButton, &QPushButton::clicked,
                  [this]() { this->duplicateMatchClicked(); });

    auto deleteMatchButton =
        new QPushButton(AppIcon(AppIcon::Type::Delete), "");
    deleteMatchButton->setToolTip(obs_module_text(
        "customTournament.configuration.deleteMatchButtonTooltip"));
    this->connect(deleteMatchButton, &QPushButton::clicked,
                  [this]() { this->deleteMatchClicked(); });

    auto moveUpButton = new QPushButton(AppIcon(AppIcon::Type::ArrowUpward), "");
    // TODO: refactor these button styles
    moveUpButton->setStyleSheet("QPushButton {"
                                "background-color: transparent;"
                                "}");
    this->connect(moveUpButton, &QPushButton::clicked,
                  [this]() { this->moveUpClicked(); });

    auto moveDownButton = new QPushButton(AppIcon(AppIcon::Type::ArrowDownward), "");
    // TODO: refactor these button styles
    moveDownButton->setStyleSheet("QPushButton {"
                                "background-color: transparent;"
                                "}");
    this->connect(moveDownButton, &QPushButton::clicked,
                  [this]() { this->moveDownClicked(); });

    // auto moveButtons = new QVBoxLayout();
    // moveButtons->addWidget(moveUpButton);
    // moveButtons->addWidget(moveDownButton);

    auto matchLabel =new QLabel(matchLabelText.c_str());
    matchLabel->setAlignment(Qt::AlignCenter);

    auto firstColumnLayout = new QVBoxLayout();
    firstColumnLayout->addWidget(moveUpButton);
    firstColumnLayout->addWidget(matchLabel);
    firstColumnLayout->addWidget(moveDownButton);

    auto frameLayout = new QHBoxLayout();
    // frameLayout->addWidget(new QLabel("TODO match config frame"));
    frameLayout->addLayout(firstColumnLayout, 0);
    frameLayout->addWidget(this->participant1Input, 1);
    frameLayout->addWidget(
        new QLabel(obs_module_text("customTournament.configuration.versus")),
        0);
    frameLayout->addWidget(this->participant2Input, 1);
    frameLayout->addWidget(duplicateMatchButton, 0);
    frameLayout->addWidget(deleteMatchButton, 0);
    // frameLayout->addLayout(moveButtons, 0);
    this->setLayout(frameLayout);
    Logger::log(LOG_DEBUG,
                "[CustomTournamentMatchConfigurationFrame] end of constructor");
}

CustomTournamentMatchConfigurationFrame::
    ~CustomTournamentMatchConfigurationFrame()
{
}

// void CustomTournamentMatchConfigurationFrame::duplicateMatch() {
//     Logger::log("[CustomTournamentMatchConfigurationFrame::duplicateMatch()] TODO");
// }
//
// void CustomTournamentMatchConfigurationFrame::deleteMatch() {
//     Logger::log("[CustomTournamentMatchConfigurationFrame::deleteMatch()] TODO");
// }

// void CustomTournamentMatchConfigurationFrame::setPlayers(
//     const std::vector<PlayerReference> &playerReferences)
// {
//     this->participant1Input->setPlayers(playerReferences);
//     this->participant2Input->setPlayers(playerReferences);
// }
//
// void CustomTournamentMatchConfigurationFrame::setMatches(
//     const std::vector<MatchReference> &matchReferences)
// {
//     this->participant1Input->setMatches(matchReferences);
//     this->participant2Input->setMatches(matchReferences);
// }
