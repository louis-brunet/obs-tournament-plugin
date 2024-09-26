#pragma once

#include "src/data/match-reference.hpp"
#include "src/data/tournament-round-reference.hpp"
#include <QFrame>
#include <QBoxLayout>

class CustomTournamentStartedRoundFrame : public QFrame {
    Q_OBJECT;

public:
    CustomTournamentStartedRoundFrame(TournamentRoundReference roundReference);
    ~CustomTournamentStartedRoundFrame();

    void notifyNewMatchState(const MatchReference &updatedMatch);

signals:
    void matchEnded(const MatchReference &matchReference);
    void matchUnended(const MatchReference &matchReference);
    void scoreChanged(const MatchReference &matchReference);

private:
    QBoxLayout *_matchListLayout;
};
