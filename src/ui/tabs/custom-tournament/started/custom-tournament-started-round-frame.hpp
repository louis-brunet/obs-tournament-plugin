#pragma once

#include "src/data/match-reference.hpp"
#include "src/data/tournament-round-reference.hpp"
#include <QFrame>

class CustomTournamentStartedRoundFrame : public QFrame {
    Q_OBJECT;

public:
    CustomTournamentStartedRoundFrame(TournamentRoundReference roundReference);
    ~CustomTournamentStartedRoundFrame();

signals:
    void matchEnded(const MatchReference &matchReference);
    void matchUnended(const MatchReference &matchReference);
};
