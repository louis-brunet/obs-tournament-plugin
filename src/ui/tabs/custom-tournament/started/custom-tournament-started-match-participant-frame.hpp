#pragma once

#include "src/data/match-participant.hpp"
#include <QFrame>

class CustomTournamentStartedMatchParticipantFrame : public QFrame {
public:
    CustomTournamentStartedMatchParticipantFrame(std::shared_ptr<MatchParticipant> matchParticipant);
    ~CustomTournamentStartedMatchParticipantFrame();
};
