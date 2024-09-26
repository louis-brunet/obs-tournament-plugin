#pragma once

#include "src/ui/dialogs/base-dialog.hpp"
#include <QMainWindow>

class PluginDialog : public BaseDialog {

public:
    PluginDialog(QMainWindow *parent);
    ~PluginDialog();

private:
    QTabWidget *_tabWidget;
};
