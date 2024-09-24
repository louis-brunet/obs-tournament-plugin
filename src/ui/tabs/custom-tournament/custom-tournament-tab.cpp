#include "custom-tournament-tab.hpp"
#include "src/data/tournament-reference.hpp"
#include "src/data/tournament.hpp"
#include "src/logger.hpp"
#include "src/ui/tabs/custom-tournament/configuration/custom-tournament-configuration-frame.hpp"
#include "src/ui/tabs/custom-tournament/started/custom-tournament-started-frame.hpp"
#include <qlabel.h>

CustomTournamentTab::CustomTournamentTab(TournamentReference tournamentReference)
    : BaseTab(tournamentReference.tournament()->name())
{
    this->_configurationFrame =
        new CustomTournamentConfigurationFrame(tournamentReference);
    this->connect(this->_configurationFrame,
                  &CustomTournamentConfigurationFrame::tournamentConfigured,
                  [this, tournamentReference]() {
                      this->endTournamentConfiguration(tournamentReference);
                  });

    this->_startedFrame = new CustomTournamentStartedFrame(tournamentReference);
    this->_startedFrame->setVisible(false);

    this->_tabContentLayout->addWidget(this->_configurationFrame);
    this->_tabContentLayout->addWidget(this->_startedFrame);
    // this->_tabContentLayout->addWidget(new QLabel("TODO custom tournament tab"));

    std::shared_ptr<Tournament> tournament = tournamentReference.tournament();
    if (tournament->isStarted()) {
        this->endTournamentConfiguration(tournamentReference);
    }
}

CustomTournamentTab::~CustomTournamentTab() {}

void CustomTournamentTab::endTournamentConfiguration(
    TournamentReference tournamentReference)
{
    tournamentReference.tournament()->setStarted(true);

    this->_configurationFrame->setVisible(false);
    this->_startedFrame->setVisible(true);

    Logger::log("[CustomTournamentTab::endTournamentConfiguration()] TODO");
}
