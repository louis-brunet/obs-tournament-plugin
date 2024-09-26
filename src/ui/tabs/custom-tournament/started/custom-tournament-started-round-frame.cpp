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

    auto matchListLayout = new QVBoxLayout();
    matchListLayout->setAlignment(Qt::AlignTop);

    // for (auto match : round->matches()) {
    for (unsigned long matchIndex = 0; matchIndex < round->matches().size();
         matchIndex++) {
        MatchReference matchReference(roundReference, (long long)matchIndex);
        auto matchFrame = new CustomTournamentStartedMatchFrame(matchReference);
        // matchFrame->xon
        matchListLayout->addWidget(matchFrame);

        this->connect(
            matchFrame, &CustomTournamentStartedMatchFrame::matchEnded,
            [this, matchReference]() { this->matchEnded(matchReference); });
        this->connect(
            matchFrame, &CustomTournamentStartedMatchFrame::matchUnended,
            [this, matchReference]() { this->matchUnended(matchReference); });
    }

    auto frameLayout = new QVBoxLayout();
    frameLayout->setContentsMargins(0, 0, 0, 0);
    frameLayout->addLayout(roundInfoLayout);
    frameLayout->addLayout(matchListLayout);
    this->setLayout(frameLayout);
}

CustomTournamentStartedRoundFrame::~CustomTournamentStartedRoundFrame() {}
