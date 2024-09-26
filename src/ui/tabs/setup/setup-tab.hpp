#pragma once

#include "src/ui/tabs/base-tab.hpp"
#include "src/ui/tabs/setup/create-tournament-frame.hpp"
#include "src/ui/tabs/setup/debug-frame.hpp"
#include <QTabWidget>

class SetupTab : public BaseTab {
    // Q_OBJECT;

public:
    SetupTab(QTabWidget *tabWidget);
    ~SetupTab();

private:
    QTabWidget *_tabWidget;
    CreateTournamentFrame *_createTournamentWidget;
    DebugFrame *_debugFrame;
};
