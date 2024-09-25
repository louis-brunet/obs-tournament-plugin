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
        matchListLayout->addWidget(matchFrame);
    }

    auto frameLayout = new QVBoxLayout();
    frameLayout->setContentsMargins(0, 0, 0, 0);
    frameLayout->addLayout(roundInfoLayout);
    frameLayout->addLayout(matchListLayout);
    this->setLayout(frameLayout);
}

CustomTournamentStartedRoundFrame::~CustomTournamentStartedRoundFrame() {}
