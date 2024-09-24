#include "custom-tournament-round-configuration-frame.hpp"
#include "src/data/match-reference-remap.hpp"
#include "src/data/match-reference.hpp"
#include "src/data/tournament.hpp"
#include "src/logger.hpp"
#include "src/ui/components/button.hpp"
#include "src/ui/components/icon.hpp"
#include "src/ui/components/labeled-input.hpp"
#include "src/ui/components/line-edit.hpp"
#include "src/ui/tabs/custom-tournament/configuration/custom-tournament-match-configuration-frame.hpp"
#include <obs-module.h>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPushButton>
#include <util/c99defs.h>

CustomTournamentRoundConfigurationFrame::CustomTournamentRoundConfigurationFrame(
    std::shared_ptr<TournamentRound> tournamentRound,
    TournamentRoundReference roundReference)
    : _tournamentRound(tournamentRound),
      _roundReference(roundReference)
{
    Logger::log(
        "[CustomTournamentRoundConfigurationFrame] constructor called, roundIndex=%d, tournamentIndex=%d",
        this->_roundReference.roundIndex,
        this->_roundReference.tournamentReference.tournamentIndex);

    auto roundNameLineEdit = new AppLineEdit();
    roundNameLineEdit->setText(this->_tournamentRound->name().c_str());
    roundNameLineEdit->setPlaceholderText(obs_module_text(
        "customTournament.configuration.roundNameInputPlaceholder"));
    this->connect(roundNameLineEdit, &AppLineEdit::textChanged,
                  [this, roundNameLineEdit]() {
                      this->_tournamentRound->setName(
                          roundNameLineEdit->text().toStdString());
                  });

    auto roundNameInput = new AppLabeledInput(
        obs_module_text("customTournament.configuration.roundNameInputLabel"),
        roundNameLineEdit);

    auto duplicateRoundButton =
        new AppButton("", AppIcon(AppIcon::Type::Copy), AppButton::Style::Transparent);
        // new QPushButton(AppIcon(AppIcon::Type::Copy), "");
    duplicateRoundButton->setToolTip(obs_module_text(
        "customTournament.configuration.duplicateRoundButtonTooltip"));
    this->connect(duplicateRoundButton, &QPushButton::clicked,
                  [this]() { this->duplicateRoundClicked(); });

    auto deleteRoundButton =
        new AppButton("", AppIcon(AppIcon::Type::Delete), AppButton::Style::Transparent);
        // new QPushButton(AppIcon(AppIcon::Type::Delete), "");
    deleteRoundButton->setToolTip(obs_module_text(
        "customTournament.configuration.deleteRoundButtonTooltip"));
    this->connect(deleteRoundButton, &QPushButton::clicked,
                  [this]() { this->deleteRoundClicked(); });

    auto roundConfigLayout = new QHBoxLayout();
    roundConfigLayout->addWidget(roundNameInput, 1);
    roundConfigLayout->addWidget(duplicateRoundButton, 0);
    roundConfigLayout->addWidget(deleteRoundButton, 0);
    this->matchListLayout = new QVBoxLayout();
    this->matchListLayout->setAlignment(Qt::AlignTop);

    // this->_matchListLayout->addWidget(new QLabel("TODO round config"));

    auto addMatchButton = new AppButton(
        obs_module_text("customTournament.configuration.addMatchButton"),
        AppIcon(AppIcon::Type::Add));
    // new QPushButton(
    // AppIcon(AppIcon::Type::Add),
    // obs_module_text("customTournament.configuration.addMatchButton"));
    this->connect(addMatchButton, &QPushButton::clicked, [this]() {
        auto addedMatchReference = this->addNewMatch();
        auto remap = MatchReferenceRemapAddedMatch(addedMatchReference);
        this->matchCountChanged(remap);
    });

    auto matchListButtons = new QHBoxLayout();
    matchListButtons->setAlignment(Qt::AlignRight);
    matchListButtons->addWidget(addMatchButton);

    auto tournamentMatches = this->_tournamentRound->matches();
    if (tournamentMatches.size() > 0) {
        this->refreshMatchList();
        // for (auto match : tournamentMatches) {
        // 	this->addExistingMatch(match);
        // }
    }
    //    else {
    // 	this->addNewMatch();
    // }

    auto frameLayout = new QVBoxLayout();
    frameLayout->setAlignment(Qt::AlignTop);
    frameLayout->setContentsMargins(0, 0, 0, 0);
    frameLayout->addLayout(roundConfigLayout, 0);
    frameLayout->addLayout(this->matchListLayout, 0); // 1);
    frameLayout->addLayout(matchListButtons, 0);

    // this->setContentsMargins(0, 0, 0, 0);
    this->setLayout(frameLayout);
    // this->setObjectName("roundConfig");
    // this->setStyleSheet("QFrame#" + this->objectName() +
    // 		    " {"
    // 		    "border-left-width: 1;"
    // 		    "border-style: solid;"
    // 		    "border-color: rgb(10, 10, 10)"
    // 		    "}");
}

CustomTournamentRoundConfigurationFrame::
    ~CustomTournamentRoundConfigurationFrame()
{
}

MatchReference CustomTournamentRoundConfigurationFrame::addNewMatch()
{
    auto newMatchIndex = this->_tournamentRound->matches().size();
    auto newMatch = std::make_shared<Match>();
    // this->_tournamentRound->matches().push_back(newMatch);
    this->_tournamentRound->addMatch(newMatch);

    this->addExistingMatch(newMatch, newMatchIndex);

    return MatchReference(this->_roundReference, (long long)newMatchIndex);
}

void CustomTournamentRoundConfigurationFrame::addExistingMatch(
    std::shared_ptr<Match> match, unsigned long matchIndexInRound)
{
    MatchReference matchReference(this->_roundReference,
                                  (long long)matchIndexInRound);
    // auto matchLabel = matchLabelFromMatchReference(matchReference);

    // auto matchIndex = this->_matchListLayout->count();
    auto newMatchConfigurationFrame =
        new CustomTournamentMatchConfigurationFrame(match, matchReference);

    this->connect(
        newMatchConfigurationFrame,
        &CustomTournamentMatchConfigurationFrame::duplicateMatchClicked,
        [this, match]() {
            auto newMatchIndex = this->_tournamentRound->duplicateMatch(match);
            if (newMatchIndex >= 0) {
                // this->refreshMatchList();

                // TODO: should probably notify which match references to update
                //  Could try to create map of updated references here (including in matches in other rounds in this tournament)
                MatchReference addedMatchReference(this->_roundReference,
                                                   newMatchIndex);
                auto remap = MatchReferenceRemapAddedMatch(addedMatchReference);
                this->matchCountChanged(remap);
            }
        });

    this->connect(
        newMatchConfigurationFrame,
        &CustomTournamentMatchConfigurationFrame::deleteMatchClicked,
        [this, match, matchReference]() { //, newMatchConfigurationFrame]() {
            auto isDeleted = this->_tournamentRound->deleteMatch(match);
            if (isDeleted) {
                auto remap = MatchReferenceRemapDeletedMatch(matchReference);
                this->matchCountChanged(remap);
            }
        });

    this->connect(newMatchConfigurationFrame,
                  &CustomTournamentMatchConfigurationFrame::swapPreviousClicked,
                  [this, matchReference]() { //, newMatchConfigurationFrame]() {
                      auto isSwapped = this->_tournamentRound->swapPrevious(
                          matchReference.matchIndex);

                      if (isSwapped) {
                          auto remap = MatchReferenceRemapSwappedMatch(
                              matchReference,
                              MatchReference(matchReference.roundReference,
                                             matchReference.matchIndex - 1));
                          this->matchCountChanged(remap);
                      }
                  });

    this->connect(newMatchConfigurationFrame,
                  &CustomTournamentMatchConfigurationFrame::swapNextClicked,
                  [this, matchReference]() { //, newMatchConfigurationFrame]() {
                      auto isSwapped = this->_tournamentRound->swapNext(
                          matchReference.matchIndex);

                      if (isSwapped) {
                          auto remap = MatchReferenceRemapSwappedMatch(
                              matchReference,
                              MatchReference(matchReference.roundReference,
                                             matchReference.matchIndex + 1));
                          this->matchCountChanged(remap);
                      }
                  });

    this->matchListLayout->addWidget(newMatchConfigurationFrame);
}

void CustomTournamentRoundConfigurationFrame::refreshMatchList()
{
    QLayoutItem *item;
    while ((item = this->matchListLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // auto rounds =
    // 	this->_roundReference.tournamentReference.tournament()->rounds();
    // auto roundIndex = this->_roundReference.roundIndex;
    // if (roundIndex < 0) {
    // 	throw std::runtime_error(
    // 		"[CustomTournamentRoundConfigurationFrame::refreshMatchList] roundIndex is negative");
    // }
    //
    // unsigned long previousMatchCount = 0;
    // for (unsigned long previousRoundIndex = 0;
    //      previousRoundIndex < (unsigned long)roundIndex;
    //      previousRoundIndex++) {
    // 	previousMatchCount +=
    // 		rounds.at(previousRoundIndex)->matches().size();
    // }
    //
    // unsigned long totalMatchIndex = previousMatchCount;
    // for (auto existingMatch : this->_tournamentRound->matches()) {
    // unsigned long matchIndexInRound = 0;
    for (unsigned long matchIndexInRound = 0;
         matchIndexInRound < this->_tournamentRound->matches().size();
         matchIndexInRound++) {
        auto existingMatch =
            this->_tournamentRound->matches().at(matchIndexInRound);
        // MatchReference matchReference(this->_roundReference,
        // 			      (long long)matchIndexInRound);
        // auto matchLabel = matchLabelFromTotal;
        this->addExistingMatch(existingMatch, matchIndexInRound);
        // ,
        //      totalMatchIndex);
        // totalMatchIndex++;
    }
}

// void CustomTournamentRoundConfigurationFrame::duplicateRound()
// {
// 	Logger::log(
// 		"[CustomTournamentRoundConfigurationFrame::duplicateRound()] TODO");
// }
//
// void CustomTournamentRoundConfigurationFrame::deleteRound()
// {
// 	Logger::log(
// 		"[CustomTournamentRoundConfigurationFrame::deleteRound()] TODO");
// }

// void CustomTournamentRoundConfigurationFrame::setPlayers(
//     const std::vector<PlayerReference> &playerReferences)
// {
//     for (int i = 0; i < this->matchListLayout->count(); i++) {
//         auto matchConfigFrame =
//             reinterpret_cast<CustomTournamentMatchConfigurationFrame *>(
//                 this->matchListLayout->itemAt(i)->widget());
//         matchConfigFrame->setPlayers(playerReferences);
//     }
// }
//
// void CustomTournamentRoundConfigurationFrame::setMatches(
//     const std::vector<MatchReference> &matchReferences)
// {
//     for (int i = 0; i < this->matchListLayout->count(); i++) {
//         auto matchConfigFrame =
//             reinterpret_cast<CustomTournamentMatchConfigurationFrame *>(
//                 this->matchListLayout->itemAt(i)->widget());
//         matchConfigFrame->setMatches(matchReferences);
//     }
// }
