#include "custom-tournament-started-frame.hpp"
#include "src/data/tournament-round-reference.hpp"
#include "src/data/tournament.hpp"
#include "src/ui/tabs/custom-tournament/started/custom-tournament-started-outputs-frame.hpp"
#include "src/ui/tabs/custom-tournament/started/custom-tournament-started-round-frame.hpp"
#include <QLabel>

CustomTournamentStartedFrame::CustomTournamentStartedFrame()
{
    this->_outputsFrame = new CustomTournamentStartedOutputsFrame();

    this->_roundListLayout = new QVBoxLayout();

    auto frameLayout = new QVBoxLayout();
    frameLayout->setContentsMargins(0, 0, 0, 0);
    frameLayout->addWidget(this->_outputsFrame);
    frameLayout->addLayout(this->_roundListLayout);

    this->setLayout(frameLayout);
}

CustomTournamentStartedFrame::~CustomTournamentStartedFrame() {}

void CustomTournamentStartedFrame::setTournament(
    TournamentReference tournamentReference)
{
    this->_outputsFrame->setTournament(tournamentReference);

    std::shared_ptr<Tournament> tournament = tournamentReference.tournament();

    QLayoutItem *roundItem;
    while ((roundItem = this->_roundListLayout->takeAt(0)) != nullptr) {
        delete roundItem->widget();
        delete roundItem;
    }

    // for (auto round : tournament->rounds()) {
    for (unsigned long roundIndex = 0; roundIndex < tournament->rounds().size();
         roundIndex++) {
        TournamentRoundReference roundReference(tournamentReference,
                                                (long long)roundIndex);
        auto roundWidget =
            new CustomTournamentStartedRoundFrame(roundReference);
        this->_roundListLayout->addWidget(roundWidget);
    }
}
