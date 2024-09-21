#pragma once

#include "src/ui/dialogs/base-dialog.hpp"
#include <qmainwindow.h>

class PluginDialog : public BaseDialog {

public:
	PluginDialog(QMainWindow *parent);
	~PluginDialog();

private:
};
