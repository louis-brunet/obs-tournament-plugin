#include "custom-tournament-started-round-frame.hpp"
#include "src/data/match-reference.hpp"
#include "src/data/tournament-round-reference.hpp"
#include "src/ui/tabs/custom-tournament/started/custom-tournament-started-match-frame.hpp"
#include <QBoxLayout>
#include <QLabel>

CustomTournamentStartedRoundFrame::CustomTournamentStartedRoundFrame(
    TournamentRoundReference roundReference)
{
    auto round = roundReference.round();

    auto roundInfoLayout = new QHBoxLayout();
    roundInfoLayout->addWidget(new QLabel(round->name().c_str()));

    this->_matchListLayout = new QVBoxLayout();
    this->_matchListLayout->setAlignment(Qt::AlignTop);

    // for (auto match : round->matches()) {
    for (unsigned long matchIndex = 0; matchIndex < round->matches().size();
         matchIndex++) {
        MatchReference matchReference(roundReference, (long long)matchIndex);
        auto matchFrame = new CustomTournamentStartedMatchFrame(matchReference);
        // matchFrame->xon
        this->_matchListLayout->addWidget(matchFrame);

        this->connect(
            matchFrame, &CustomTournamentStartedMatchFrame::matchEnded,
            [this, matchReference]() { this->matchEnded(matchReference); });
        this->connect(
            matchFrame, &CustomTournamentStartedMatchFrame::matchUnended,
            [this, matchReference]() { this->matchUnended(matchReference); });
        this->connect(
            matchFrame, &CustomTournamentStartedMatchFrame::scoreChanged,
            [this, matchReference]() { this->scoreChanged(matchReference); });
    }

    auto frameLayout = new QVBoxLayout();
    frameLayout->setContentsMargins(0, 0, 0, 0);
    frameLayout->addLayout(roundInfoLayout);
    frameLayout->addLayout(this->_matchListLayout);
    this->setLayout(frameLayout);
}

CustomTournamentStartedRoundFrame::~CustomTournamentStartedRoundFrame() {}

void CustomTournamentStartedRoundFrame::notifyNewMatchState(
    const MatchReference &updatedMatch)
{
    for (int matchIndex = 0; matchIndex < this->_matchListLayout->count();
         matchIndex++) {
        auto layoutItem = this->_matchListLayout->itemAt(matchIndex);
        auto roundFrame =
            (CustomTournamentStartedMatchFrame *)layoutItem->widget();
        roundFrame->notifyNewMatchState(updatedMatch);
    }
}
