#pragma once

#include "src/data/tournament-reference.hpp"
#include "src/ui/tabs/custom-tournament/started/custom-tournament-started-outputs-frame.hpp"
#include <QFrame>
#include <QBoxLayout>

class CustomTournamentStartedFrame : public QFrame {
    Q_OBJECT;

public:
    CustomTournamentStartedFrame();
    ~CustomTournamentStartedFrame();

    void setTournament(TournamentReference tournamentReference);

private:
    QBoxLayout *_roundListLayout;
    CustomTournamentStartedOutputsFrame *_outputsFrame;
};
