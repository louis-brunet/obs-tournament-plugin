#pragma once

#include "src/data/match-reference.hpp"
#include <QFrame>

class CustomTournamentStartedMatchFrame : public QFrame {
    Q_OBJECT;

public:
    CustomTournamentStartedMatchFrame(MatchReference matchReference);
    ~CustomTournamentStartedMatchFrame();

signals:
    void matchEnded();
    void matchUnended();
};
