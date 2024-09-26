#include "match-participant-input.hpp"
#include "src/data/match-participant-from-match.hpp"
#include "src/data/match-participant-player.hpp"
#include "src/data/match-participant-unknown.hpp"
#include "src/data/player-reference.hpp"
#include "src/logger.hpp"
#include <QBoxLayout>
#include <obs-module.h>
#include <stdexcept>

MatchParticipantInput::MatchParticipantInput()
// std::shared_ptr<MatchParticipant> existingParticipant)
// : participantOnReset(existingParticipant)
{
    this->playerComboBox = new QComboBox();
    // auto playerEmptyData = new PlayerComboBoxData();
    // this->playerComboBox->addItem("", (long long)playerEmptyData);
    // this->playerComboBox->addItem("test item", (long long)playerEmptyData);
    this->connect(this->playerComboBox, &QComboBox::currentIndexChanged,
                  [this](int comboBoxIndex) {
                      UNUSED_PARAMETER(comboBoxIndex);

                      auto newMatchParticipant = this->toMatchParticipant();

                      switch (newMatchParticipant->type()) {
                      case MatchParticipant::ParticipantFromMatch:
                          this->fromMatchComboBox->setVisible(true);
                          break;
                      case MatchParticipant::ParticipantUnknown:
                      case MatchParticipant::ParticipantPlayer:
                      default:
                          this->fromMatchComboBox->setVisible(false);
                          break;
                      }

                      this->participantChanged(newMatchParticipant);
                  });

    this->fromMatchComboBox = new QComboBox();
    // auto fromMatchEmptyData = new FromMatchComboBoxData();
    // this->fromMatchComboBox->addItem("", (long long)fromMatchEmptyData);
    this->fromMatchComboBox->setVisible(false);
    this->connect(this->fromMatchComboBox, &QComboBox::currentIndexChanged,
                  [this](int comboBoxIndex) {
                      UNUSED_PARAMETER(comboBoxIndex);

                      auto newMatchParticipant = this->toMatchParticipant();
                      this->participantChanged(newMatchParticipant);
                  });

    auto frameLayout = new QVBoxLayout();
    frameLayout->addWidget(this->playerComboBox);
    frameLayout->addWidget(this->fromMatchComboBox);
    this->setLayout(frameLayout);
}

MatchParticipantInput::~MatchParticipantInput() {}

std::shared_ptr<MatchParticipant>
MatchParticipantInput::toMatchParticipant() const
{
    auto currentIndex = this->playerComboBox->currentIndex();
    // Logger::log("[toMatchParticipant] currentIndex=%d", currentIndex);
    // Logger::log("[toMatchParticipant] data type=%d", ((PlayerComboBoxData *)(long long)(this->playerComboBox->currentData().toLongLong()))->type);
    PlayerComboBoxData playerComboBoxData;
    if (currentIndex >= 0) {
        playerComboBoxData = *reinterpret_cast<PlayerComboBoxData *>(
            this->playerComboBox->itemData(currentIndex).toLongLong());
    } else {
        playerComboBoxData = PlayerComboBoxData();
    }
    // auto playerComboBoxData = static_cast<PlayerComboBoxData *>(
    //     this->playerComboBox->currentData().data());

    std::shared_ptr<MatchParticipant> newMatchParticipant;
    switch (playerComboBoxData.type) {
    case PlayerComboBoxData::Unknown: {
        newMatchParticipant = std::make_shared<MatchParticipantUnknown>();
        break;
    }

    case PlayerComboBoxData::Player: {
        newMatchParticipant = std::make_shared<MatchParticipantPlayer>(
            playerComboBoxData.playerReference);
        break;
    }

    case PlayerComboBoxData::WinnerOf: {
        // MatchReference fromMatchReference(roundReference);
        auto fromMatchComboBoxData = reinterpret_cast<FromMatchComboBoxData *>(
            this->fromMatchComboBox->currentData().toLongLong());

        // switch (fromMatchComboBoxData->type) {
        // case FromMatchComboBoxData::Unknown:
        //     break;
        // case FromMatchComboBoxData::Match:
        newMatchParticipant = std::make_shared<MatchParticipantFromMatch>(
            fromMatchComboBoxData->fromMatchReference,
            std::make_unique<SelectWinnerOfMatch>());
        //     break;
        // }
        break;
    }

    case PlayerComboBoxData::LoserOf: {
        auto fromMatchComboBoxData = reinterpret_cast<FromMatchComboBoxData *>(
            this->fromMatchComboBox->currentData().toLongLong());

        newMatchParticipant = std::make_shared<MatchParticipantFromMatch>(
            fromMatchComboBoxData->fromMatchReference,
            std::make_unique<SelectLoserOfMatch>());
        break;
    }

    default:
        Logger::error("[toMatchParticipant] unrecognized enum variant : %d",
                      playerComboBoxData.type);
        throw std::runtime_error("unrecognized enum variant");
    }

    return newMatchParticipant;
}

void MatchParticipantInput::setPlayers(
    const std::vector<PlayerReference> &players)
{
    this->playerComboBox->clear();

    auto emptyPlayerData = new PlayerComboBoxData();
    this->playerComboBox->addItem("", (long long)emptyPlayerData);

    auto winnerOfData =
        new PlayerComboBoxData(PlayerComboBoxData::Type::WinnerOf);
    this->playerComboBox->addItem(
        obs_module_text(
            "customTournament.configuration.matchParticipant.winnerOf"),
        (long long)winnerOfData);

    auto loserOfData =
        new PlayerComboBoxData(PlayerComboBoxData::Type::LoserOf);
    this->playerComboBox->addItem(
        obs_module_text(
            "customTournament.configuration.matchParticipant.loserOf"),
        (long long)loserOfData);

    for (auto playerReference : players) {
        auto player = playerReference.player();
        auto playerData = new PlayerComboBoxData(playerReference);
        this->playerComboBox->addItem(player->name().c_str(),
                                      (long long)playerData);
    }

    // if (this->participantOnReset) {
    //     switch (this->participantOnReset->type()) {
    //     case MatchParticipant::Type::Player: {
    //         auto participantPlayer =
    //             std::reinterpret_pointer_cast<MatchParticipantPlayer>(
    //                 this->participantOnReset);
    //         auto foundIndex = this->playerComboBox->findText(
    //             participantPlayer->playerReference().player()->name().c_str());
    //         this->playerComboBox->setCurrentIndex(foundIndex);
    //         break;
    //     }
    //
    //     case MatchParticipant::Type::FromMatch: {
    //         auto participantFromMatch =
    //             std::reinterpret_pointer_cast<MatchParticipantFromMatch>(
    //                 this->participantOnReset);
    //
    //         switch (participantFromMatch->selectionStrategy()) {
    //         case MatchParticipantSelectionStrategy::Loser:
    //             this->playerComboBox->setCurrentIndex(
    //                 this->playerComboBox->findData((long long)loserOfData));
    //             break;
    //
    //         case MatchParticipantSelectionStrategy::Winner:
    //             this->playerComboBox->setCurrentIndex(
    //                 this->playerComboBox->findData((long long)winnerOfData));
    //             break;
    //
    //         case MatchParticipantSelectionStrategy::Unknown:
    //             break;
    //         }
    //
    //         break;
    //     }
    //     case MatchParticipant::Type::Unknown:
    //         break;
    //     }
    //
    //     this->participantOnReset = nullptr;
    // }
}

void MatchParticipantInput::setParticipant(
    const std::shared_ptr<MatchParticipant> participant)
{
    switch (participant->type()) {
    case MatchParticipant::Type::ParticipantPlayer: {
        auto participantPlayer =
            std::reinterpret_pointer_cast<MatchParticipantPlayer>(participant);
        auto foundIndex = this->playerComboBox->findText(
            participantPlayer->playerReference().player()->name().c_str());
        this->playerComboBox->setCurrentIndex(foundIndex);
        break;
    }

    case MatchParticipant::Type::ParticipantFromMatch: {
        auto participantFromMatch =
            std::reinterpret_pointer_cast<MatchParticipantFromMatch>(
                participant);
        if (participantFromMatch->fromMatchReference().match()) {
            auto fromMatchLabel =
                participantFromMatch->fromMatchReference().toMatchLabel();
            Logger::log("[MatchParticipantInput::setParticipant] from match %s",
                        fromMatchLabel.c_str());
            this->fromMatchComboBox->setCurrentIndex(
                this->fromMatchComboBox->findText(fromMatchLabel.c_str()));
        }

        switch (participantFromMatch->selectionStrategy()) {
        case MatchParticipantSelectionStrategy::Loser:
            this->playerComboBox->setCurrentIndex(
                2); // TODO: better way than hardcoding index ?

            // this->playerComboBox->findData((long long)loserOfData));
            break;

        case MatchParticipantSelectionStrategy::Winner:
            this->playerComboBox->setCurrentIndex(
                1); // TODO: better way than hardcoding index ?

            // this->playerComboBox->findData((long long)winnerOfData));
            break;

        case MatchParticipantSelectionStrategy::Unknown:
            break;
        }

        break;
    }
    case MatchParticipant::Type::ParticipantUnknown:
        break;
    }
}

void MatchParticipantInput::setMatches(
    const std::vector<MatchReference> &matches)
{
    this->fromMatchComboBox->clear();

    auto emptyFromMatchData = new FromMatchComboBoxData();
    this->fromMatchComboBox->addItem("", (long long)emptyFromMatchData);
    // Logger::log(
    //     "[MatchParticipantInput::setMatches] adding empty data : matchIndex=%d, roundIndex=%d, tournamentIndex=%d ",
    //     emptyFromMatchData->fromMatchReference.matchIndex,
    //     emptyFromMatchData->fromMatchReference.roundReference.roundIndex,
    //     emptyFromMatchData->fromMatchReference.roundReference
    //         .tournamentReference.tournamentIndex);

    for (auto matchReference : matches) {
        // Logger::log(
        //     "[MatchParticipantInput::setMatches] adding match %s reference, matchIndex=%d, roundIndex=%d, tournamentIndex=%d ",
        //     matchReference.toMatchLabel().c_str(), matchReference.matchIndex,
        //     matchReference.roundReference.roundIndex,
        //     matchReference.roundReference.tournamentReference.tournamentIndex);

        auto match = matchReference.match();
        auto matchData = new FromMatchComboBoxData(matchReference);
        this->fromMatchComboBox->addItem(matchReference.toMatchLabel().c_str(),
                                         (long long)matchData);
    }
}

PlayerComboBoxData::PlayerComboBoxData(PlayerComboBoxData::Type _type)
    : type(_type)
{
}

PlayerComboBoxData::PlayerComboBoxData(PlayerReference _playerReference)
    : PlayerComboBoxData(PlayerComboBoxData::Type::Player)
{
    this->playerReference = _playerReference;
}

PlayerComboBoxData::~PlayerComboBoxData() {}

// FromMatchComboBoxData::FromMatchComboBoxData(FromMatchComboBoxData::Type _type)
//     : type(_type)
// {
// }
FromMatchComboBoxData::FromMatchComboBoxData(MatchReference _fromMatchReference)
    : fromMatchReference(_fromMatchReference)
{
}

FromMatchComboBoxData::~FromMatchComboBoxData() {}
