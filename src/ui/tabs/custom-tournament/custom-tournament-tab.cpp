#include "custom-tournament-tab.hpp"
#include "src/ui/tabs/custom-tournament/configuration/custom-tournament-configuration-frame.hpp"
#include <qlabel.h>

CustomTournamentTab::CustomTournamentTab(std::shared_ptr<Tournament> tournament)
	: BaseTab(tournament->name())
{

    this->_tabContentLayout->addWidget(new CustomTournamentConfigurationFrame(tournament));
    // this->_tabContentLayout->addWidget(new QLabel("TODO custom tournament tab"));
}

CustomTournamentTab::~CustomTournamentTab() {}
