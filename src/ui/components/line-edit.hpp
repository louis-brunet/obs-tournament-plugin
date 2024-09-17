#pragma once

#include <QLineEdit>

class AppLineEdit : public QLineEdit {
    Q_OBJECT;

public:
    AppLineEdit();
    ~AppLineEdit();

private:
    void updateTextColorStyleSheet();
};
