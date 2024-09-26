#include "line-edit.hpp"

AppLineEdit::AppLineEdit(const char *initialText, QWidget *parent)
    : QLineEdit(initialText, parent)
{
    // this->setFocus(Qt::FocusReason::MouseFocusReason);
    this->connect(this, &QLineEdit::textChanged,
                  [this]() { this->updateTextColorStyleSheet(); });

    // this->setMaximumWidth(400);
    this->updateTextColorStyleSheet();
}

AppLineEdit::~AppLineEdit() {}

void AppLineEdit::updateTextColorStyleSheet()
{
    if (this->text().isEmpty()) {
        this->setStyleSheet("QLineEdit { color: gray; }");
    } else {
        this->setStyleSheet("QLineEdit { color: white; }");
    }
}
