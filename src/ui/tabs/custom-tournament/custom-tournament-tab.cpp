#include "custom-tournament-tab.hpp"
#include <qlabel.h>

CustomTournamentTab::CustomTournamentTab(Tournament &tournament)
	: BaseTab(tournament.name())
{
    this->_tabContentLayout->addWidget(new QLabel("TODO custom tournament tab"));
}

CustomTournamentTab::~CustomTournamentTab() {}
