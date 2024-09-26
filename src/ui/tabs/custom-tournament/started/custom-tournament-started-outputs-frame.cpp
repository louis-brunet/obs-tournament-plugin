#include "custom-tournament-started-outputs-frame.hpp"
#include "src/data/match-reference.hpp"
#include "src/data/tournament-round-reference.hpp"
#include "src/data/tournament.hpp"
#include "src/logger.hpp"
#include "src/ui/tabs/custom-tournament/started/source-combo-box.hpp"
#include <QLabel>
#include <QBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <obs-module.h>

CustomTournamentStartedOutputsFrame::CustomTournamentStartedOutputsFrame()
    : QGroupBox(obs_module_text("customTournament.output.outputFrameTitle"))
{
    this->_currentMatchComboBox = new QComboBox();
    auto currentMatchInput = new AppLabeledInput(
        obs_module_text("customTournament.output.currentMatch"),
        this->_currentMatchComboBox);

    this->_upcomingMatchComboBox = new QComboBox();
    auto upcomingMatchInput = new AppLabeledInput(
        obs_module_text("customTournament.output.upcomingMatch"),
        this->_upcomingMatchComboBox);
    // this->connect(this->_currentMatchComboBox, &QComboBox::currentIndexChanged,
    //               [this](int currentIndex) {
    //                   UNUSED_PARAMETER(currentIndex);
    //                   MatchReference *matchReference =
    //                       (MatchReference *)this->_currentMatchComboBox
    //                           ->currentData()
    //                           .toLongLong();
    //                   this->setCurrentMatchOutputs(matchReference);
    //               });

    this->_participant1NameInput = new SourceComboBox(
        obs_module_text("customTournament.output.participant1Name"),
        SourceComboBox::Type::TextSource);
    this->_participant2NameInput = new SourceComboBox(
        obs_module_text("customTournament.output.participant2Name"),
        SourceComboBox::Type::TextSource);

    this->_participant1ImageInput = new SourceComboBox(
        obs_module_text("customTournament.output.participant1Image"),
        SourceComboBox::Type::ImageSource);
    this->_participant2ImageInput = new SourceComboBox(
        obs_module_text("customTournament.output.participant2Image"),
        SourceComboBox::Type::ImageSource);

    this->_participant1ScoreInput = new SourceComboBox(
        obs_module_text("customTournament.output.participant1Score"),
        SourceComboBox::Type::TextSource);
    this->_participant2ScoreInput = new SourceComboBox(
        obs_module_text("customTournament.output.participant2Score"),
        SourceComboBox::Type::TextSource);

    this->_participant1DescriptionInput = new SourceComboBox(
        obs_module_text("customTournament.output.participant1Description"),
        SourceComboBox::Type::TextSource);
    this->_participant2DescriptionInput = new SourceComboBox(
        obs_module_text("customTournament.output.participant2Description"),
        SourceComboBox::Type::TextSource);

    auto updateOutputSourcesButton = new QPushButton(
        obs_module_text("customTournament.output.updateOutputSourcesButton"));
    this->connect(updateOutputSourcesButton, &QPushButton::clicked,
                  [this]() { this->updateOutputSources(); });

    auto frameLayout = new QGridLayout();
    // frameLayout->setContentsMargins(0, 0, 0, 0);
    frameLayout->addWidget(currentMatchInput, 0, 0);
    frameLayout->addWidget(this->_participant1NameInput, 1, 0);
    frameLayout->addWidget(this->_participant2NameInput, 1, 1);
    frameLayout->addWidget(this->_participant1ImageInput, 2, 0);
    frameLayout->addWidget(this->_participant2ImageInput, 2, 1);
    frameLayout->addWidget(this->_participant1ScoreInput, 3, 0);
    frameLayout->addWidget(this->_participant2ScoreInput, 3, 1);
    frameLayout->addWidget(this->_participant1DescriptionInput, 4, 0);
    frameLayout->addWidget(this->_participant2DescriptionInput, 4, 1);
    frameLayout->addWidget(upcomingMatchInput, 5, 0);
    frameLayout->addWidget(updateOutputSourcesButton, 6, 0, 1, 2);

    this->setLayout(frameLayout);
}

CustomTournamentStartedOutputsFrame::~CustomTournamentStartedOutputsFrame() {}

void CustomTournamentStartedOutputsFrame::setMatchSelection(
    QComboBox *comboBox, const TournamentReference &tournamentReference,
    const MatchReference &referenceToSelect,
    std::function<void(MatchReference *)> selectionChangedCallback)
{
    int indexToSelect = -1;
    comboBox->clear();
    comboBox->addItem("", (long long)nullptr);

    auto tournament = tournamentReference.tournament();

    for (unsigned long roundIndex = 0; roundIndex < tournament->rounds().size();
         roundIndex++) {
        auto round = tournament->rounds()[roundIndex];
        TournamentRoundReference roundReference(tournamentReference,
                                                (long long)roundIndex);

        for (unsigned long matchIndex = 0; matchIndex < round->matches().size();
             matchIndex++) {
            auto match = round->matches()[matchIndex];
            // MatchReference matchReference(roundReference, (long long)matchIndex);
            auto matchReference =
                new MatchReference(roundReference, (long long)matchIndex);

            if (*matchReference == referenceToSelect) {
                indexToSelect = comboBox->count();
            }

            comboBox->addItem(matchReference->toMatchLabel().c_str(),
                              (long long)matchReference);
        }
    }

    this->disconnect(comboBox, &QComboBox::currentIndexChanged, nullptr,
                     nullptr);
    if (indexToSelect >= 0) {
        comboBox->setCurrentIndex(indexToSelect);
    }
    this->connect(
        comboBox, &QComboBox::currentIndexChanged,
        [this, comboBox, selectionChangedCallback](int currentIndex) {
            UNUSED_PARAMETER(currentIndex);

            MatchReference *matchReference =
                (MatchReference *)comboBox->currentData().toLongLong();

            selectionChangedCallback(matchReference);
            //
            // if (matchReference) {
            //     tournament->outputs.currentMatch = *matchReference;
            // } else {
            //     tournament->outputs.currentMatch.matchIndex = -1;
            // }
            //
            this->updateOutputSources();
        });
}

void CustomTournamentStartedOutputsFrame::setTournament(
    TournamentReference tournamentReference)
{
    auto tournament = tournamentReference.tournament();

    this->setMatchSelection(
        this->_currentMatchComboBox, tournamentReference,
        tournament->outputs.currentMatch,
        [tournament](MatchReference *selectedReference) {
            if (selectedReference) {
                tournament->outputs.currentMatch = *selectedReference;
            } else {

                tournament->outputs.currentMatch.matchIndex = -1;
            }
        });

    this->setMatchSelection(
        this->_upcomingMatchComboBox, tournamentReference,
        tournament->outputs.upcomingMatch,
        [tournament](MatchReference *selectedReference) {
            if (selectedReference) {
                tournament->outputs.upcomingMatch = *selectedReference;
            } else {

                tournament->outputs.upcomingMatch.matchIndex = -1;
            }
        });

    // int currentMatchIndex = -1;
    // this->_currentMatchComboBox->clear();
    // this->_currentMatchComboBox->addItem("", (long long)nullptr);
    //
    // for (unsigned long roundIndex = 0; roundIndex < tournament->rounds().size();
    //      roundIndex++) {
    //     auto round = tournament->rounds()[roundIndex];
    //     TournamentRoundReference roundReference(tournamentReference,
    //                                             (long long)roundIndex);
    //
    //     for (unsigned long matchIndex = 0; matchIndex < round->matches().size();
    //          matchIndex++) {
    //         auto match = round->matches()[matchIndex];
    //         // MatchReference matchReference(roundReference, (long long)matchIndex);
    //         auto matchReference =
    //             new MatchReference(roundReference, (long long)matchIndex);
    //
    //         if (*matchReference == tournament->outputs.currentMatch) {
    //             currentMatchIndex = this->_currentMatchComboBox->count();
    //         }
    //
    //         this->_currentMatchComboBox->addItem(
    //             matchReference->toMatchLabel().c_str(),
    //             (long long)matchReference);
    //     }
    // }
    //
    // this->disconnect(this->_currentMatchComboBox,
    //                  &QComboBox::currentIndexChanged, nullptr, nullptr);
    // if (currentMatchIndex >= 0) {
    //     this->_currentMatchComboBox->setCurrentIndex(currentMatchIndex);
    // }
    // this->connect(this->_currentMatchComboBox, &QComboBox::currentIndexChanged,
    //               [this, tournament](int currentIndex) {
    //                   UNUSED_PARAMETER(currentIndex);
    //
    //                   MatchReference *matchReference =
    //                       (MatchReference *)this->_currentMatchComboBox
    //                           ->currentData()
    //                           .toLongLong();
    //                   if (matchReference) {
    //                       tournament->outputs.currentMatch = *matchReference;
    //                   } else {
    //                       tournament->outputs.currentMatch.matchIndex = -1;
    //                   }
    //
    //                   this->updateOutputSources();
    //               });

    this->disconnect(this->_participant1NameInput,
                     &SourceComboBox::sourceChanged, nullptr, nullptr);
    this->_participant1NameInput->setCurrentSource(
        tournament->outputs.participant1Name.sourceUuid.c_str());
    this->connect(this->_participant1NameInput, &SourceComboBox::sourceChanged,
                  [tournament](std::string newUuid) {
                      tournament->outputs.participant1Name.sourceUuid = newUuid;
                      // TODO: change displayed source text here?
                  });

    this->disconnect(this->_participant2NameInput,
                     &SourceComboBox::sourceChanged, nullptr, nullptr);
    this->_participant2NameInput->setCurrentSource(
        tournament->outputs.participant2Name.sourceUuid.c_str());
    this->connect(this->_participant2NameInput, &SourceComboBox::sourceChanged,
                  [tournament](std::string newUuid) {
                      tournament->outputs.participant2Name.sourceUuid = newUuid;
                      // TODO: change displayed source text here?
                  });

    this->disconnect(this->_participant1ImageInput,
                     &SourceComboBox::sourceChanged, nullptr, nullptr);
    this->_participant1ImageInput->setCurrentSource(
        tournament->outputs.participant1Image.sourceUuid.c_str());
    this->connect(this->_participant1ImageInput, &SourceComboBox::sourceChanged,
                  [tournament](std::string newUuid) {
                      tournament->outputs.participant1Image.sourceUuid =
                          newUuid;
                      // TODO: change displayed source image here?
                  });

    this->disconnect(this->_participant2ImageInput,
                     &SourceComboBox::sourceChanged, nullptr, nullptr);
    this->_participant2ImageInput->setCurrentSource(
        tournament->outputs.participant2Image.sourceUuid.c_str());
    this->connect(this->_participant2ImageInput, &SourceComboBox::sourceChanged,
                  [tournament](std::string newUuid) {
                      tournament->outputs.participant2Image.sourceUuid =
                          newUuid;
                      // TODO: change displayed source image here?
                  });

    this->disconnect(this->_participant1ScoreInput,
                     &SourceComboBox::sourceChanged, nullptr, nullptr);
    this->_participant1ScoreInput->setCurrentSource(
        tournament->outputs.participant1Score.sourceUuid.c_str());
    this->connect(this->_participant1ScoreInput, &SourceComboBox::sourceChanged,
                  [tournament](std::string newUuid) {
                      tournament->outputs.participant1Score.sourceUuid =
                          newUuid;
                      // TODO: change displayed source text here?
                  });

    this->disconnect(this->_participant2ScoreInput,
                     &SourceComboBox::sourceChanged, nullptr, nullptr);
    this->_participant2ScoreInput->setCurrentSource(
        tournament->outputs.participant2Score.sourceUuid.c_str());
    this->connect(this->_participant2ScoreInput, &SourceComboBox::sourceChanged,
                  [tournament](std::string newUuid) {
                      tournament->outputs.participant2Score.sourceUuid =
                          newUuid;
                      // TODO: change displayed source text here?
                  });

    this->disconnect(this->_participant1DescriptionInput,
                     &SourceComboBox::sourceChanged, nullptr, nullptr);
    this->_participant1DescriptionInput->setCurrentSource(
        tournament->outputs.participant1Description.sourceUuid.c_str());
    this->connect(
        this->_participant1DescriptionInput, &SourceComboBox::sourceChanged,
        [tournament](std::string newUuid) {
            tournament->outputs.participant1Description.sourceUuid = newUuid;
            // TODO: change displayed source text here?
        });

    this->disconnect(this->_participant2DescriptionInput,
                     &SourceComboBox::sourceChanged, nullptr, nullptr);
    this->_participant2DescriptionInput->setCurrentSource(
        tournament->outputs.participant2Description.sourceUuid.c_str());
    this->connect(
        this->_participant2DescriptionInput, &SourceComboBox::sourceChanged,
        [tournament](std::string newUuid) {
            tournament->outputs.participant2Description.sourceUuid = newUuid;
            // TODO: change displayed source text here?
        });

    // TODO: ? when more inputs are added
}

void CustomTournamentStartedOutputsFrame::updateOutputSources()
{
    auto currentMatchReference =
        (MatchReference *)this->_currentMatchComboBox->currentData()
            .toLongLong();

    // std::shared_ptr<Player> determinedPlayer1;
    // std::shared_ptr<Player> determinedPlayer2;

    auto match = currentMatchReference->match();
    auto tournament =
        currentMatchReference->roundReference.tournamentReference.tournament();
    auto outputs = tournament->outputs;

    if (currentMatchReference) {
        Logger::log("setting match %s outputs",
                    currentMatchReference->toMatchLabel().c_str());

        // determinedPlayer1 = match->participant1()->determinedPlayer();
        // determinedPlayer2 = match->participant2()->determinedPlayer();
        auto participant1 = match->participant1();
        auto participant2 = match->participant2();
        auto player1 = participant1->determinedPlayer();
        auto player2 = participant2->determinedPlayer();

        if (player1) {
            outputs.participant1Name.setSourceText(player1->name().c_str());
            outputs.participant1Score.setSourceText(
                std::to_string((unsigned int)match->participant1Score).c_str());
            outputs.participant1Image.setSourceImageFile(
                player1->imagePath().c_str());
            outputs.participant1Description.setSourceText(
                player1->description().c_str());
        } else {
            outputs.participant1Name.setSourceText(
                participant1->displayName().c_str());
            outputs.participant1Score.setSourceText("-");
            outputs.participant1Image.setSourceImageFile("");
            outputs.participant1Description.setSourceText("-");
        }

        if (player2) {
            outputs.participant2Name.setSourceText(player2->name().c_str());
            outputs.participant2Score.setSourceText(
                std::to_string((unsigned int)match->participant2Score).c_str());
            outputs.participant2Image.setSourceImageFile(
                player2->imagePath().c_str());
            outputs.participant2Description.setSourceText(
                player2->description().c_str());
        } else {
            outputs.participant2Name.setSourceText(
                participant2->displayName().c_str());
            outputs.participant2Score.setSourceText("-");
            outputs.participant2Image.setSourceImageFile("");
            outputs.participant2Description.setSourceText("-");
        }
    } else {
        Logger::log("resetting match outputs");

        outputs.participant1Name.setSourceText("-");
        outputs.participant1Score.setSourceText("-");
        outputs.participant1Image.setSourceImageFile("");
        outputs.participant1Description.setSourceText("-");

        outputs.participant2Name.setSourceText("-");
        outputs.participant2Score.setSourceText("-");
        outputs.participant2Image.setSourceImageFile("");
        outputs.participant2Description.setSourceText("-");
    }
}

void CustomTournamentStartedOutputsFrame::onScoreChanged(
    const MatchReference &updatedMatch)
{
    auto currentMatchReference =
        (MatchReference *)this->_currentMatchComboBox->currentData()
            .toLongLong();
    if (currentMatchReference && *currentMatchReference == updatedMatch) {
        auto match = currentMatchReference->match();
        auto tournament = currentMatchReference->roundReference
                              .tournamentReference.tournament();
        auto outputs = tournament->outputs;

        outputs.participant1Score.setSourceText(
            std::to_string((unsigned int)match->participant1Score).c_str());
        outputs.participant2Score.setSourceText(
            std::to_string((unsigned int)match->participant2Score).c_str());
    }
}
