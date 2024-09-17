#pragma once

#include "src/ui/dialogs/base-dialog.hpp"

class ErrorDialog : public BaseDialog {

public:
	ErrorDialog(QWidget *parent, const char *message);
	~ErrorDialog();

private:
};
