#include "custom-tournament-started-match-participant-frame.hpp"
#include <QBoxLayout>
#include <QLabel>

CustomTournamentStartedMatchParticipantFrame::
    CustomTournamentStartedMatchParticipantFrame(
        std::shared_ptr<MatchParticipant> matchParticipant)
{
    auto frameLayout = new QVBoxLayout();
    frameLayout->setContentsMargins(0, 0, 0, 0);
    frameLayout->addWidget(new QLabel(matchParticipant->displayName().c_str())); //, 0);
    this->setLayout(frameLayout);
}

CustomTournamentStartedMatchParticipantFrame::
    ~CustomTournamentStartedMatchParticipantFrame()
{
}
