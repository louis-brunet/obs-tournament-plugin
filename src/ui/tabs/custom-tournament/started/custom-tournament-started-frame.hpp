#pragma once

#include "src/data/tournament-reference.hpp"
#include <QFrame>
#include <QBoxLayout>

class CustomTournamentStartedFrame : public QFrame {
    Q_OBJECT;

public:
    CustomTournamentStartedFrame(TournamentReference tournamentReference);
    ~CustomTournamentStartedFrame();

private:
};
