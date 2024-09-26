#pragma once

#include <QDialog>

class BaseDialog : public QDialog {
    Q_OBJECT;

public:
    BaseDialog(QWidget *parent, const char *windowTitle, int minWidth,
               int minHeight);
    ~BaseDialog();

private:
};
