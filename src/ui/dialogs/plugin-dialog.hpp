#pragma once

#include "src/model/plugin-data.hpp"
#include "src/plugin-support.h"
#include "src/ui/dialogs/base-dialog.hpp"
#include <QTabWidget>
#include <QMainWindow>

class TournamentPluginDialog : public BaseDialog {
	// Q_OBJECT;

public:
    // static TournamentPluginDialog *getInstance();
	TournamentPluginDialog(std::string pluginVersion = PLUGIN_VERSION, QMainWindow *parent = nullptr);

	~TournamentPluginDialog();

private:
    static TournamentPluginDialog *instance;

	std::string pluginVersion;
	QTabWidget *tabsWidget;


    void loadData(const TournamentPluginData *pluginData);
};

