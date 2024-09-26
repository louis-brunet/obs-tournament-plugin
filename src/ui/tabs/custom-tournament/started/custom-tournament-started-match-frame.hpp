#pragma once

#include "src/data/match-reference.hpp"
#include "src/ui/tabs/custom-tournament/started/custom-tournament-started-score-frame.hpp"
#include <QCheckBox>
#include <QFrame>
#include <QLabel>

class CustomTournamentStartedMatchFrame : public QFrame {
    Q_OBJECT;

public:
    CustomTournamentStartedMatchFrame(MatchReference matchReference);
    ~CustomTournamentStartedMatchFrame();

    void notifyNewMatchState(const MatchReference &updatedMatch);

signals:
    void matchEnded();
    void matchUnended();
    void scoreChanged();

private:
    QLabel *_participant1Label;
    QLabel *_participant2Label;
    CustomTournamentStartedScoreFrame *_participant1Score;
    CustomTournamentStartedScoreFrame *_participant2Score;
    QCheckBox *_isDoneCheckbox;
    QCheckBox *_isStartedCheckbox;
    MatchReference _matchReference;

    void updateMatchStateFromDeterminedPlayers();
};
