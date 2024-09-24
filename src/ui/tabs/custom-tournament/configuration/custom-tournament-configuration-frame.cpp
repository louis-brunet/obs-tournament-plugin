#include "custom-tournament-configuration-frame.hpp"
#include "src/data/match-reference-remap.hpp"
#include "src/data/match-reference.hpp"
#include "src/data/player-reference.hpp"
#include "src/data/tournament-round-reference.hpp"
#include "src/data/tournament-round.hpp"
#include "src/data/tournament.hpp"
#include "src/logger.hpp"
#include "src/ui/components/button.hpp"
#include "src/ui/components/icon.hpp"
#include "src/ui/tabs/custom-tournament/configuration/custom-tournament-match-configuration-frame.hpp"
#include "src/ui/tabs/custom-tournament/configuration/custom-tournament-round-configuration-frame.hpp"
#include <QBoxLayout>
#include <deque>
#include <obs-module.h>
#include <qpushbutton.h>

CustomTournamentConfigurationFrame::CustomTournamentConfigurationFrame(
    TournamentReference tournamentReference)
    : // _tournament(tournament),
      _tournamentReference(tournamentReference)
{
    Logger::log("[CustomTournamentConfigurationFrame] constructor called");

    this->_roundListLayout = new QVBoxLayout();
    this->_roundListLayout->setAlignment(Qt::AlignTop);
    // for (auto round : tournament)
    // addRound

    auto addRoundButton = new AppButton(
        obs_module_text("customTournament.configuration.addRoundButton"),
        AppIcon(AppIcon::Type::Add));
    // new QPushButton(
    // AppIcon(AppIcon::Type::Add),
    // obs_module_text("customTournament.configuration.addRoundButton"));
    this->connect(addRoundButton, &QPushButton::clicked,
                  [this]() { this->addNewRound(); });

    auto roundListButtons = new QHBoxLayout();
    roundListButtons->setAlignment(Qt::AlignRight);
    roundListButtons->addWidget(addRoundButton);

    std::shared_ptr<Tournament> tournament =
        this->_tournamentReference.tournament();
    auto tournamentRounds = tournament->rounds();
    if (tournamentRounds.size() > 0) {
        Logger::log(
            "[CustomTournamentConfigurationFrame] adding existing rounds");
        this->refreshRoundList();
    } else {
        // Logger::log(
        //     "[CustomTournamentConfigurationFrame] no existing rounds, adding new round");
        // this->addNewRound();
    }

    auto endTournamentConfigurationButton = new AppButton(obs_module_text(
        "customTournament.configuration.endConfigurationButton"));
    this->connect(endTournamentConfigurationButton, &QPushButton::clicked,
                  [this]() { this->endTournamentConfiguration(); });

    auto bottomLayout = new QVBoxLayout();
    bottomLayout->setAlignment(Qt::AlignBottom);
    bottomLayout->addWidget(endTournamentConfigurationButton);

    auto frameLayout = new QVBoxLayout();
    frameLayout->addLayout(this->_roundListLayout, 0);
    frameLayout->addLayout(roundListButtons, 0);
    frameLayout->addLayout(bottomLayout, 1);

    this->setLayout(frameLayout);
}

CustomTournamentConfigurationFrame::~CustomTournamentConfigurationFrame() {}

void CustomTournamentConfigurationFrame::addNewRound()
{

    auto roundIndex = this->_tournamentReference.tournament()->rounds().size();
    auto newRound = std::make_shared<TournamentRound>();
    this->_tournamentReference.tournament()->rounds().push_back(newRound);

    this->addExistingRound(newRound, roundIndex);
}

void CustomTournamentConfigurationFrame::addExistingRound(
    std::shared_ptr<TournamentRound> round, unsigned long roundIndex)
{
    TournamentRoundReference roundReference(this->_tournamentReference,
                                            (long long)roundIndex);
    auto newRoundConfigurationFrame =
        new CustomTournamentRoundConfigurationFrame(round, roundReference);
    this->_roundListLayout->addWidget(newRoundConfigurationFrame);

    this->connect(newRoundConfigurationFrame,
                  &CustomTournamentRoundConfigurationFrame::matchCountChanged,
                  [this, roundIndex](const MatchReferenceRemap &remap) {
                      this->refreshRoundList(roundIndex, remap);
                  });

    this->connect(
        newRoundConfigurationFrame,
        &CustomTournamentRoundConfigurationFrame::duplicateRoundClicked,
        [this, roundReference]() {
            auto newRoundIndex =
                roundReference.tournamentReference.tournament()->duplicateRound(
                    roundReference.roundIndex);
            if (newRoundIndex >= 0) {
                TournamentRoundReference addedRoundReference(
                    roundReference.tournamentReference, newRoundIndex);

                auto remap =
                    MatchReferenceRemapDuplicatedRound(addedRoundReference);
                this->refreshRoundList((unsigned long)newRoundIndex, remap);
            }
        });

    this->connect(newRoundConfigurationFrame,
                  &CustomTournamentRoundConfigurationFrame::deleteRoundClicked,
                  [this, roundReference]() {
                      auto isDeleted =
                          this->_tournamentReference.tournament()->deleteRound(
                              roundReference.roundIndex);
                      if (isDeleted) {
                          auto remap =
                              MatchReferenceRemapDeletedRound(roundReference);
                          this->refreshRoundList(
                              (unsigned long)roundReference.roundIndex, remap);
                      }
                  });
}

void CustomTournamentConfigurationFrame::refreshRoundList(
    unsigned long startingRoundIndex, const MatchReferenceRemap &remap)
{
    QLayoutItem *item;
    while ((item = this->_roundListLayout->takeAt((int)startingRoundIndex)) !=
           nullptr) {
        delete item->widget();
        delete item;
    }

    auto rounds = this->_tournamentReference.tournament()->rounds();

    // for (auto round : this->_tournament->rounds()) {
    for (unsigned long roundIndex = startingRoundIndex;
         roundIndex < rounds.size(); roundIndex++) {
        auto round = rounds.at(roundIndex);
        this->addExistingRound(round, roundIndex);
    }

    this->updatePlayerChoices(remap); //startingRoundIndex);
}

void CustomTournamentConfigurationFrame::updatePlayerChoices(
    const MatchReferenceRemap &remap)
// unsigned long startingRoundIndex)
// const std::vector<PlayerReference> &playerReferences,
// const std::vector<MatchReference> &matchReferences)
{
    std::vector<PlayerReference> playerReferences;
    for (unsigned long playerIndex = 0;
         playerIndex <
         this->_tournamentReference.tournament()->players().size();
         playerIndex++) {
        PlayerReference playerReference(this->_tournamentReference,
                                        (long long)playerIndex);
        playerReferences.push_back(playerReference);
    }
    Logger::log("[updatePlayerChoices] found %d players",
                playerReferences.size());

    std::vector<MatchReference> matchReferences;
    // long long totalMatchIndex = 0;
    for (unsigned long roundIndex = 0;
         roundIndex < this->_tournamentReference.tournament()->rounds().size();
         roundIndex++) {
        TournamentRoundReference roundReference(this->_tournamentReference,
                                                (long long)roundIndex);
        auto round =
            this->_tournamentReference.tournament()->rounds().at(roundIndex);
        for (unsigned long matchIndexInRound = 0;
             matchIndexInRound < round->matches().size(); matchIndexInRound++) {
            // MatchReference matchReference(roundReference,
            //                               (long long)matchIndexInRound);

            matchReferences.push_back(
                MatchReference(roundReference, (long long)matchIndexInRound));
            // totalMatchIndex++;
        }
    }
    Logger::log("[updatePlayerChoices] found %d matches",
                matchReferences.size());

    std::deque<std::shared_ptr<MatchParticipant>> participantsToReset;
    // for (auto round : this->_tournamentReference.tournament()->rounds()) {
    //     for (auto match : round->matches()) {
    auto rounds = this->_tournamentReference.tournament()->rounds();
    for (unsigned long roundIndex = 0; roundIndex < rounds.size();
         roundIndex++) {
        auto round = rounds[roundIndex];
        auto matches = round->matches();
        TournamentRoundReference roundReference(this->_tournamentReference,
                                                (long long)roundIndex);

        for (unsigned long matchIndex = 0; matchIndex < matches.size();
             matchIndex++) {
            auto match = matches[matchIndex];
            MatchReference remapContextReference(roundReference,
                                                 (long long)matchIndex);
            match->participant1()->applyRemap(&remap, remapContextReference);
            match->participant2()->applyRemap(&remap, remapContextReference);

            participantsToReset.push_back(match->participant1());
            participantsToReset.push_back(match->participant2());
        }
    }

    for (unsigned long roundIndex = 0;
         (int)roundIndex < this->_roundListLayout->count(); roundIndex++) {
        auto roundConfigFrame =
            (CustomTournamentRoundConfigurationFrame *)this->_roundListLayout
                ->itemAt((int)roundIndex)
                ->widget();

        // roundConfigFrame->setPlayers(playerReferences);
        // roundConfigFrame->setMatches(matchReferences);

        auto matchListLayout = roundConfigFrame->matchListLayout;
        for (unsigned long matchIndex = 0;
             (int)matchIndex < matchListLayout->count(); matchIndex++) {
            auto matchConfigFrame =
                (CustomTournamentMatchConfigurationFrame *)matchListLayout
                    ->itemAt((int)matchIndex)
                    ->widget();
            matchConfigFrame->participant1Input->setPlayers(playerReferences);
            matchConfigFrame->participant1Input->setMatches(matchReferences);

            matchConfigFrame->participant2Input->setPlayers(playerReferences);
            matchConfigFrame->participant2Input->setMatches(matchReferences);

            auto nextParticipant = participantsToReset.front();
            participantsToReset.pop_front();
            matchConfigFrame->participant1Input->setParticipant(
                nextParticipant);

            nextParticipant = participantsToReset.front();
            participantsToReset.pop_front();
            matchConfigFrame->participant2Input->setParticipant(
                nextParticipant);
        }
    }
}

void CustomTournamentConfigurationFrame::endTournamentConfiguration() {
    Logger::log("[CustomTournamentConfigurationFrame::endTournamentConfiguration] TODO validation");

    this->tournamentConfigured();
}
