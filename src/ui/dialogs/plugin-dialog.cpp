#include "plugin-dialog.hpp"
#include "src/data/plugin-data.hpp"
#include "src/data/tournament-reference.hpp"
#include "src/ui/dialogs/error-dialog.hpp"
#include "src/ui/tabs/custom-tournament/custom-tournament-tab.hpp"
#include "src/ui/tabs/setup/setup-tab.hpp"
#include <memory>
#include <obs-module.h>
#include <QBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QTabWidget>

int pluginDialogWidth = 0;
int pluginDialogHeight = 0;
int pluginDialogMinWidth = 600;
int pluginDialogMinHeight = 200;

PluginDialog::PluginDialog(QMainWindow *parent)
    : BaseDialog(parent, obs_module_text("plugin.name"), pluginDialogMinWidth,
                 pluginDialogMinHeight)
{
    auto vlayout = new QVBoxLayout;
    vlayout->setContentsMargins(11, 11, 11, 11);
    vlayout->setAlignment(Qt::AlignTop);
    // vlayout->addWidget(this->tabsWidget);
    // vlayout->addLayout(bottomLayout);
    this->setLayout(vlayout);

    // auto scrollArea = new QScrollArea();
    // scrollArea->setLayout(tabLayout);
    // vlayout

    this->_tabWidget = new QTabWidget();
    // tabWidget->addTab(new QLabel("TODO plugin dialog"), "abc");
    vlayout->addWidget(this->_tabWidget);

    auto setupTab = new SetupTab(this->_tabWidget);
    this->_tabWidget->addTab(setupTab, setupTab->tabTitle());

    // for (auto tournament : pluginData->tournaments) {
    TournamentReference tournamentReference;
    std::shared_ptr<Tournament> tournament;
    QWidget *tournamentTab;

    for (unsigned long tournamentIndex = 0;
         tournamentIndex < pluginData->tournaments.size(); tournamentIndex++) {
        tournament = pluginData->tournaments.at(tournamentIndex);
        tournamentReference = TournamentReference((long long)tournamentIndex);

        switch (tournament->type()) {
        case Tournament::Unknown: {
            auto errorDialog = new ErrorDialog(
                this,
                obs_module_text("error.loadDialog.unknownTournamentType"));
            errorDialog->show();
            continue;
        }

        case Tournament::Custom: {
            tournamentTab = new CustomTournamentTab(tournamentReference);
            break;
        }

        default:
            throw std::runtime_error("unrecognized enum value");
        }
        this->_tabWidget->addTab(tournamentTab, tournament->name().c_str());
    }
    this->_tabWidget->setCurrentIndex(this->_tabWidget->count() - 1);

    if (pluginDialogWidth > pluginDialogMinWidth &&
        pluginDialogHeight > pluginDialogMinHeight) {
        this->resize(pluginDialogWidth, pluginDialogHeight);
    }
}

PluginDialog::~PluginDialog()
{
    // while (this->_tabWidget->count() != 0) {
    //     QWidget *tab = this->_tabWidget->widget(0);
    //     this->_tabWidget->removeTab(0);
    //     delete tab;
    // }
    // delete this->_tabWidget;
    // this->_tabWidget = nullptr;
}
