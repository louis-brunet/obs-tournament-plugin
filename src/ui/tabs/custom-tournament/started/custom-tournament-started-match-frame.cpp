#include "custom-tournament-started-match-frame.hpp"
#include "src/logger.hpp"
#include "src/ui/tabs/custom-tournament/started/custom-tournament-started-score-frame.hpp"
#include <QBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <obs-module.h>

CustomTournamentStartedMatchFrame::CustomTournamentStartedMatchFrame(
    MatchReference matchReference)
{
    auto match = matchReference.match();

    auto matchLabel = new QLabel(matchReference.toMatchLabel().c_str());
    // auto participant1Frame =
    //     new CustomTournamentStartedMatchParticipantFrame(match->participant1());
    auto participant1Label =
        new QLabel(match->participant1()->displayName().c_str());
    participant1Label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    auto participant1Score =
        new CustomTournamentStartedScoreFrame(match->participant1Score);
    this->connect(participant1Score,
                  &CustomTournamentStartedScoreFrame::scoreChanged,
                  [match](unsigned char newScore) {
                      match->participant1Score = newScore;
                  });

    // auto participant2Frame =
    //     new CustomTournamentStartedMatchParticipantFrame(match->participant2());
    auto participant2Label =
        new QLabel(match->participant2()->displayName().c_str());
    participant2Label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    auto participant2Score =
        new CustomTournamentStartedScoreFrame(match->participant2Score);
    this->connect(participant2Score,
                  &CustomTournamentStartedScoreFrame::scoreChanged,
                  [match](unsigned char newScore) {
                      match->participant2Score = newScore;
                  });

    auto isStartedCheckbox = new QCheckBox(
        obs_module_text("customTournament.started.matchStartedCheckbox"));
    auto isDoneCheckbox = new QCheckBox(
        obs_module_text("customTournament.started.matchDoneCheckbox"));

    // auto scoreLayout = new QHBoxLayout();
    // scoreLayout->setContentsMargins(0, 0, 0, 0);
    // scoreLayout->addWidget(participant1Score);
    // scoreLayout->addWidget(participant2Score);
    isDoneCheckbox->setVisible(false);
    participant1Score->setVisible(false);
    participant2Score->setVisible(false);
    this->connect(isStartedCheckbox, &QCheckBox::stateChanged,
                  [participant1Score, participant2Score, isDoneCheckbox,
                   match](int checkBoxStateInt) {
                      auto checkBoxState = (Qt::CheckState)checkBoxStateInt;
                      Logger::log("checkbox state : %d", checkBoxState);

                      // TODO: refactor to fct callable from constructor

                      switch (checkBoxState) {

                      case Qt::Unchecked:
                      case Qt::PartiallyChecked:
                          participant1Score->setVisible(false);
                          participant2Score->setVisible(false);
                          isDoneCheckbox->setVisible(false);
                          match->state = Match::State::NotStarted;
                          break;
                      case Qt::Checked:
                          participant1Score->setVisible(true);
                          participant2Score->setVisible(true);
                          isDoneCheckbox->setVisible(true);
                          match->state = Match::State::Started;
                          break;
                      }
                  });
    this->connect(isDoneCheckbox, &QCheckBox::stateChanged,
                  [participant1Score, participant2Score, isStartedCheckbox,
                   match](int checkBoxStateInt) {
                      auto checkBoxState = (Qt::CheckState)checkBoxStateInt;
                      Logger::log("checkbox state : %d", checkBoxState);

                      // TODO: refactor to fct callable from constructor

                      switch (checkBoxState) {

                      case Qt::Unchecked:
                      case Qt::PartiallyChecked:
                          participant1Score->setEditable(true);
                          participant2Score->setEditable(true);
                          isStartedCheckbox->setVisible(true);
                          match->state = Match::State::Started;
                          break;
                      case Qt::Checked:
                          participant1Score->setEditable(false);
                          participant2Score->setEditable(false);
                          isStartedCheckbox->setVisible(false);
                          match->state = Match::State::Done;
                          break;
                      }
                  });
    // TODO: refactor to public function ?
    switch (match->state) {
    case Match::NotStarted:
        break;
    case Match::Started:
        isStartedCheckbox->setCheckState(Qt::CheckState::Checked);
        break;
    case Match::Done:
        isStartedCheckbox->setCheckState(Qt::CheckState::Checked);
        isDoneCheckbox->setCheckState(Qt::CheckState::Checked);
        break;
    }

    auto frameLayout = new QHBoxLayout();
    frameLayout->setAlignment(Qt::AlignLeft);
    frameLayout->setContentsMargins(0, 0, 0, 0);
    frameLayout->addWidget(matchLabel, 0);
    // frameLayout->addWidget(participant1Frame, 0);
    frameLayout->addWidget(participant1Label, 0);
    frameLayout->addWidget(participant1Score, 0);
    frameLayout->addWidget(participant2Score, 0);
    frameLayout->addWidget(participant2Label, 0);
    frameLayout->addWidget(isStartedCheckbox);
    frameLayout->addWidget(isDoneCheckbox);
    // frameLayout->addWidget(participant2Frame, 0);
    // if (match->participant1()->isReady() && match->participant2()->isReady()) {
    //     frameLayout->addWidget(new QLabel("ready"));
    // }
    this->setLayout(frameLayout);
}

CustomTournamentStartedMatchFrame::~CustomTournamentStartedMatchFrame() {}
