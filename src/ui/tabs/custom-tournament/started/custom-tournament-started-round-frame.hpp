#pragma once

#include "src/data/tournament-round-reference.hpp"
#include <QFrame>

class CustomTournamentStartedRoundFrame : public QFrame {
public:
    CustomTournamentStartedRoundFrame(TournamentRoundReference roundReference);
    ~CustomTournamentStartedRoundFrame();
};
