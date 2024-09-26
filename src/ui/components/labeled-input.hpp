#pragma once

#include <QWidget>

class AppLabeledInput : public QWidget {
    Q_OBJECT;

public:
    enum LabelPosition {
        Left,
        Top,
    };

    AppLabeledInput(const std::string &label, QWidget *inputWidget,
                    LabelPosition labelPosition = LabelPosition::Left);
    ~AppLabeledInput();

protected:
    QWidget *_inputWidget;
};
