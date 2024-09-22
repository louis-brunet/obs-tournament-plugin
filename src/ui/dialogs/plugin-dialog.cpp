#include "plugin-dialog.hpp"
#include "src/data/plugin-data.hpp"
#include "src/ui/dialogs/error-dialog.hpp"
#include "src/ui/tabs/custom-tournament/custom-tournament-tab.hpp"
#include "src/ui/tabs/setup/setup-tab.hpp"
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
	: BaseDialog(parent, obs_module_text("plugin.name"),
		     pluginDialogMinWidth, pluginDialogMinHeight)
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

	auto tabWidget = new QTabWidget();
	// tabWidget->addTab(new QLabel("TODO plugin dialog"), "abc");
	vlayout->addWidget(tabWidget);

	auto setupTab = new SetupTab(tabWidget);
	tabWidget->addTab(setupTab, setupTab->tabTitle());

	for (auto tournament : pluginData->tournaments) {
		QWidget *tournamentTab;
		switch (tournament->type()) {
		case Tournament::Unknown: {
			auto errorDialog = new ErrorDialog(
				this,
				obs_module_text(
					"error.loadDialog.unknownTournamentType"));
			errorDialog->show();
			continue;
		}

		case Tournament::Custom: {
			tournamentTab = new CustomTournamentTab(*tournament);
			break;
		}

		default:
			throw std::runtime_error("unrecognized enum value");
		}
		tabWidget->addTab(tournamentTab, tournament->name().c_str());
	}
	tabWidget->setCurrentIndex(tabWidget->count() - 1);

	if (pluginDialogWidth > pluginDialogMinWidth &&
	    pluginDialogHeight > pluginDialogMinHeight) {
		this->resize(pluginDialogWidth, pluginDialogHeight);
	}
}

PluginDialog::~PluginDialog() {}
