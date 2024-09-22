#pragma once

#include "src/ui/tabs/base-tab.hpp"
#include <QTabWidget>

class SetupTab : public BaseTab {
public:
    SetupTab(QTabWidget *tabWidget);
    ~SetupTab();

private:
    QTabWidget *_tabWidget;
};
