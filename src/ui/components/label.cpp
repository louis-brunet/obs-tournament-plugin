#include "label.hpp"
#include <util/c99defs.h>

AppLabel::AppLabel(const char *text, QWidget *parent, Qt::WindowFlags flags)
    : QLabel(text, parent, flags)
{
}

AppLabel::~AppLabel() {}

void AppLabel::mousePressEvent(QMouseEvent *event)
{
    UNUSED_PARAMETER(event);

    emit clicked();
}
