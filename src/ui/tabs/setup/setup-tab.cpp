#include "setup-tab.hpp"
#include "src/data/plugin-data.hpp"
#include "src/data/tournament.hpp"
#include "src/ui/tabs/setup/create-tournament-frame.hpp"
#include "src/ui/tabs/setup/debug-frame.hpp"
#include <obs-module.h>
#include <qboxlayout.h>
#include <qframe.h>
#include <qgroupbox.h>
#include <qscrollarea.h>

SetupTab::SetupTab(QTabWidget *tabWidget)
	: BaseTab(obs_module_text("setup.tabTitle")),
	  _tabWidget(tabWidget)
{
	auto createTournamentWidget = new CreateTournamentFrame();
	this->connect(createTournamentWidget,
		      &CreateTournamentFrame::tournamentCreated,
		      [this](std::shared_ptr<Tournament> newTournament,
			     QWidget *newTab) {
			      pluginData->tournaments.push_back(newTournament);
			      this->_tabWidget->addTab(
				      newTab, newTournament->name().c_str());
			      this->_tabWidget->setCurrentWidget(newTab);
			      // this->showTournamentBuilder
		      });

	auto onResetDataCallback = [this]() {
		while (this->_tabWidget->count() > 1) {
			this->_tabWidget->removeTab(1);
		}
	};

	this->_tabContentLayout->addWidget(createTournamentWidget);
	this->_tabContentLayout->addWidget(new DebugFrame(onResetDataCallback));
}

SetupTab::~SetupTab() {}
