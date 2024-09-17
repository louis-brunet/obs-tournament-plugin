#include "base-dialog.hpp"

BaseDialog::BaseDialog(QWidget *parent, const char *windowTitle, int minWidth,
		       int minHeight)
	: QDialog(parent)
{
	this->setWindowTitle(windowTitle);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setMinimumSize(minWidth, minHeight);
	this->setSizeGripEnabled(true);
}

BaseDialog::~BaseDialog() {}
