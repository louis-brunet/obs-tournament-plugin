#include "custom-tournament-tab.hpp"
#include "src/data/tournament-reference.hpp"
#include "src/data/tournament.hpp"
#include "src/ui/tabs/custom-tournament/configuration/custom-tournament-configuration-frame.hpp"
#include <qlabel.h>

CustomTournamentTab::CustomTournamentTab(TournamentReference tournamentReference)
	: BaseTab(tournamentReference.tournament()->name())
{
    this->_tabContentLayout->addWidget(new CustomTournamentConfigurationFrame(tournamentReference));
    // this->_tabContentLayout->addWidget(new QLabel("TODO custom tournament tab"));
}

CustomTournamentTab::~CustomTournamentTab() {}
