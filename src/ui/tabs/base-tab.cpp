#include "base-tab.hpp"
#include <obs-module.h>
#include <qboxlayout.h>
#include <qframe.h>
#include <qgroupbox.h>
#include <qscrollarea.h>

BaseTab::BaseTab(std::string __tabTitle) : QScrollArea(), _tabTitle(__tabTitle)
{
    auto tabWidget = new QWidget();
    this->setWidget(tabWidget);
    this->setWidgetResizable(true);

    this->_tabContentLayout = new QVBoxLayout();
    this->_tabContentLayout->setAlignment(Qt::AlignTop);
    tabWidget->setLayout(this->_tabContentLayout);

    // auto createTournamentWidget =
    // 	new QGroupBox(obs_module_text("setup.createTournament.title"));
    //    // createTournamentWidget->setMinimumHeight(200);
    // this->_tabContentLayout->addWidget(createTournamentWidget);
    //
    // for (int i = 0; i < 16; i++) {
    // 	this->_tabContentLayout->addWidget(new QGroupBox("TEST"), 0);
    // }
}

BaseTab::~BaseTab() {}

const char *BaseTab::tabTitle() const
{
    return this->_tabTitle.c_str();
}
