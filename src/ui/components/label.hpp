#pragma once

#include <qlabel.h>

class AppLabel : public QLabel {
    Q_OBJECT;

public:
    explicit AppLabel(const char *text = nullptr, QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~AppLabel();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);
};
