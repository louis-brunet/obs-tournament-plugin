#include "custom-tournament-started-frame.hpp"
#include <QLabel>

CustomTournamentStartedFrame::CustomTournamentStartedFrame(TournamentReference tournamentReference) {
    UNUSED_PARAMETER(tournamentReference);

    auto label = new QLabel("TODO started ");

    auto frameLayout = new QVBoxLayout();
    frameLayout->setContentsMargins(0, 0, 0, 0);
    frameLayout->addWidget(label);

    this->setLayout(frameLayout);
}

CustomTournamentStartedFrame::~CustomTournamentStartedFrame() {}
