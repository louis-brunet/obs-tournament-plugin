#include "custom-tournament-started-match-frame.hpp"
#include "src/logger.hpp"
#include "src/ui/tabs/custom-tournament/started/custom-tournament-started-score-frame.hpp"
#include <QBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <obs-module.h>

CustomTournamentStartedMatchFrame::CustomTournamentStartedMatchFrame(
    MatchReference matchReference)
    : _matchReference(matchReference)
{
    auto match = this->_matchReference.match();

    auto matchLabel = new QLabel(this->_matchReference.toMatchLabel().c_str());
    // auto participant1Frame =
    //     new CustomTournamentStartedMatchParticipantFrame(match->participant1());

    this->_participant1Label = new QLabel();
    // new QLabel(match->participant1()->displayName().c_str());
    // this->_participant1Label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    this->_participant1Label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    this->_participant1Score =
        new CustomTournamentStartedScoreFrame(match->participant1Score);
    this->connect(this->_participant1Score,
                  &CustomTournamentStartedScoreFrame::scoreChanged,
                  [match, this](unsigned char newScore) {
                      match->participant1Score = newScore;
                      this->scoreChanged();
                  });

    // auto participant2Frame =
    //     new CustomTournamentStartedMatchParticipantFrame(match->participant2());
    this->_participant2Label = new QLabel();
    // new QLabel(match->participant2()->displayName().c_str());
    this->_participant2Label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    this->_participant2Score =
        new CustomTournamentStartedScoreFrame(match->participant2Score);
    this->connect(this->_participant2Score,
                  &CustomTournamentStartedScoreFrame::scoreChanged,
                  [match, this](unsigned char newScore) {
                      match->participant2Score = newScore;
                      this->scoreChanged();
                  });

    this->_isStartedCheckbox = new QCheckBox(
        obs_module_text("customTournament.started.matchStartedCheckbox"));
    this->_isDoneCheckbox = new QCheckBox(
        obs_module_text("customTournament.started.matchDoneCheckbox"));

    // auto scoreLayout = new QHBoxLayout();
    // scoreLayout->setContentsMargins(0, 0, 0, 0);
    // scoreLayout->addWidget(participant1Score);
    // scoreLayout->addWidget(participant2Score);

    // .............
    // auto determinedPlayer1 = match->participant1()->determinedPlayer();
    // auto determinedPlayer2 = match->participant2()->determinedPlayer();
    // if (!determinedPlayer1 || !determinedPlayer2) {
    //     isStartedCheckbox->setVisible(false);
    //
    //     // TODO: this should not be done here, but probably before?
    //     switch (match->state) {
    //     case Match::NotStarted:
    //         break;
    //     case Match::Started:
    //     case Match::Done:
    //         match->state = Match::State::NotStarted;
    //         break;
    //     }
    // }
    // isDoneCheckbox->setVisible(false);
    // participant1Score->setVisible(false);
    // participant2Score->setVisible(false);
    this->connect(this->_isStartedCheckbox, &QCheckBox::stateChanged,
                  [this](int checkBoxStateInt) {
                      auto checkBoxState = (Qt::CheckState)checkBoxStateInt;
                      Logger::log("checkbox state : %d", checkBoxState);

                      // TODO: refactor to fct callable from constructor?

                      auto currentMatch = this->_matchReference.match();
                      switch (checkBoxState) {
                      case Qt::Unchecked:
                      case Qt::PartiallyChecked:
                          this->_participant1Score->setVisible(false);
                          this->_participant2Score->setVisible(false);
                          this->_isDoneCheckbox->setVisible(false);
                          currentMatch->state = Match::State::NotStarted;
                          break;
                      case Qt::Checked:
                          this->_participant1Score->setVisible(true);
                          this->_participant2Score->setVisible(true);
                          this->_isDoneCheckbox->setVisible(true);
                          currentMatch->state = Match::State::Started;
                          break;
                      }
                  });
    this->connect(
        this->_isDoneCheckbox, &QCheckBox::stateChanged,
        [this](int checkBoxStateInt) {
            auto checkBoxState = (Qt::CheckState)checkBoxStateInt;
            Logger::log("checkbox state : %d", checkBoxState);

            // TODO: refactor to fct callable from constructor?

            auto currentMatch = this->_matchReference.match();
            switch (checkBoxState) {
            case Qt::Unchecked:
            case Qt::PartiallyChecked: {
                this->_participant1Score->setEditable(true);
                this->_participant2Score->setEditable(true);
                this->_isStartedCheckbox->setVisible(true);
                bool wasDone = currentMatch->state == Match::State::Done;
                currentMatch->state = Match::State::Started;
                if (wasDone) {
                    this->matchUnended();
                }
                break;
            }
            case Qt::Checked: {
                this->_participant1Score->setEditable(false);
                this->_participant2Score->setEditable(false);
                this->_isStartedCheckbox->setVisible(false);
                bool wasDone = currentMatch->state == Match::State::Done;
                currentMatch->state = Match::State::Done;
                if (!wasDone) {
                    this->matchEnded();
                }
                break;
            }
            }
        });

    this->updateMatchStateFromDeterminedPlayers();
    // switch (match->state) {
    // case Match::NotStarted:
    //     break;
    // case Match::Started:
    //     isStartedCheckbox->setCheckState(Qt::CheckState::Checked);
    //     break;
    // case Match::Done:
    //     isStartedCheckbox->setCheckState(Qt::CheckState::Checked);
    //     isDoneCheckbox->setCheckState(Qt::CheckState::Checked);
    //     break;
    // }

    // auto namesLayout = new QHBoxLayout();
    // namesLayout->setContentsMargins(0, 0, 0, 0);

    auto frameLayout = new QGridLayout();
    frameLayout->setAlignment(Qt::AlignLeft);

    int contentMargin = 20;
    int vContentMargin = contentMargin;
    int hContentMargin = contentMargin;
    frameLayout->setContentsMargins(hContentMargin, vContentMargin,
                                    hContentMargin, vContentMargin);
    frameLayout->setColumnMinimumWidth(0, 30);
    frameLayout->setColumnMinimumWidth(1, 160);
    frameLayout->setColumnMinimumWidth(2, 140);
    frameLayout->setColumnMinimumWidth(3, 90);
    frameLayout->setColumnMinimumWidth(4, 90);
    frameLayout->setRowMinimumHeight(0, 30);
    frameLayout->setRowMinimumHeight(1, 30);

    frameLayout->addWidget(matchLabel, 0, 0, 2, 1, Qt::AlignLeft);
    // frameLayout->addWidget(participant1Frame, 0);
    frameLayout->addWidget(this->_participant1Label, 0, 1);
    frameLayout->addWidget(this->_participant1Score, 0, 2);
    frameLayout->addWidget(this->_participant2Score, 1, 2);
    frameLayout->addWidget(this->_participant2Label, 1, 1);
    frameLayout->addWidget(this->_isStartedCheckbox, 0, 3, 2, 1,
                           Qt::AlignCenter);
    frameLayout->addWidget(this->_isDoneCheckbox, 0, 4, 2, 1, Qt::AlignCenter);
    // frameLayout->addWidget(participant2Frame, 0);
    // if (match->participant1()->isReady() && match->participant2()->isReady()) {
    //     frameLayout->addWidget(new QLabel("ready"));
    // }
    this->setLayout(frameLayout);
    // this->setFrameStyle(QFrame::Shape::Panel | QFrame::Shadow::Raised);
}

CustomTournamentStartedMatchFrame::~CustomTournamentStartedMatchFrame() {}

void CustomTournamentStartedMatchFrame::notifyNewMatchState(
    const MatchReference &updatedMatchReference)
{
    // UNUSED_PARAMETER(updatedMatchReference);
    // auto updatedMatch = updatedMatchReference.match();
    // if (!updatedMatch) {
    //     return;
    // }

    if (this->_matchReference != updatedMatchReference) {
        this->updateMatchStateFromDeterminedPlayers();
    }
    // auto currentMatch = this->_matchReference.match();
    // this->_participant1Label->setText(currentMatch->participant1()->displayName().c_str());
    // this->_participant2Label->setText(currentMatch->participant2()->displayName().c_str());
    //
    // // auto determinedPlayer1 =
    // //     currentMatch->participant1()->determinedPlayer();
    // // auto determinedPlayer2 =
    // //     currentMatch->participant2()->determinedPlayer();
    //
    //
    // .............;

    // auto currentMatch = this->_matchReference.match();
    // if (!currentMatch) {
    //     return;
    // }
    //
    // switch (updatedMatch->state) {
    // case Match::NotStarted:
    //     break;
    //
    // case Match::Started:
    //     break;
    // case Match::Done:
    //     auto determinedPlayer1 =
    //         currentMatch->participant1()->determinedPlayer();
    //     auto determinedPlayer2 =
    //         currentMatch->participant2()->determinedPlayer();
    //
    //     if (determinedPlayer1 && determinedPlayer2 && currentMatch->state != Match::State::Done) {
    //         this->_isStartedCheckbox->setVisible(true);
    //     }
    //     break;
    // }
}

void CustomTournamentStartedMatchFrame::updateMatchStateFromDeterminedPlayers()
{
    auto match = this->_matchReference.match();

    this->_participant1Label->setText(
        match->participant1()->displayName().c_str());
    this->_participant2Label->setText(
        match->participant2()->displayName().c_str());

    this->_isStartedCheckbox->setVisible(true);
    this->_isDoneCheckbox->setVisible(true);
    this->_participant1Score->setVisible(true);
    this->_participant2Score->setVisible(true);
    // this->_isDoneCheckbox->setVisible(false);
    // this->_participant1Score->setVisible(false);
    // this->_participant2Score->setVisible(false);

    auto determinedPlayer1 = match->participant1()->determinedPlayer();
    auto determinedPlayer2 = match->participant2()->determinedPlayer();
    if (!determinedPlayer1 || !determinedPlayer2) {
        this->_isStartedCheckbox->setVisible(false);

        switch (match->state) {
        case Match::NotStarted:
            break;
        case Match::Done:
            this->_isDoneCheckbox->setCheckState(Qt::CheckState::Unchecked);
            // NOTE: no break;
        case Match::Started:
            Logger::log(
                "changing match %s state to NotStarted bc players are not determined",
                this->_matchReference.toMatchLabel().c_str());
            this->_isStartedCheckbox->setCheckState(Qt::CheckState::Unchecked);
            // match->state = Match::State::NotStarted;
            break;
        }
    }

    switch (match->state) {
    case Match::NotStarted:
        this->_participant1Score->setVisible(false);
        this->_participant2Score->setVisible(false);
        this->_isDoneCheckbox->setVisible(false);
        break;
    case Match::Started:
        // this->_participant1Score->setVisible(true);
        // this->_participant2Score->setVisible(true);
        // this->_isDoneCheckbox->setVisible(true);
        this->_isStartedCheckbox->setCheckState(Qt::CheckState::Checked);
        break;
    case Match::Done:
        this->_isStartedCheckbox->setVisible(false);
        // this->_isDoneCheckbox->setVisible(true);
        // this->_participant1Score->setVisible(true);
        // this->_participant2Score->setVisible(true);
        this->_isStartedCheckbox->setCheckState(Qt::CheckState::Checked);
        this->_isDoneCheckbox->setCheckState(Qt::CheckState::Checked);
        break;
    }
}
