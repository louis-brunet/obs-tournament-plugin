#pragma once

#include "src/data/match-reference.hpp"
#include <QFrame>

class CustomTournamentStartedMatchFrame : public QFrame {
public:
    CustomTournamentStartedMatchFrame(MatchReference matchReference);
    ~CustomTournamentStartedMatchFrame();
};
