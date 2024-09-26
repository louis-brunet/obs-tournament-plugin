#pragma once

#include <QLineEdit>
#include <QWidget>

class AppLineEdit : public QLineEdit {
    Q_OBJECT;

public:
    AppLineEdit(const char *initialText = "", QWidget *parent = nullptr);
    ~AppLineEdit();

private:
    void updateTextColorStyleSheet();
};
