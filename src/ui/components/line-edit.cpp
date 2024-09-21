#include "line-edit.hpp"

AppLineEdit::AppLineEdit(const char *_contents, QWidget *parent): QLineEdit(_contents, parent)
{
	this->connect(this, &QLineEdit::textChanged,
		      [this]() { this->updateTextColorStyleSheet(); });

    this->updateTextColorStyleSheet();
}

AppLineEdit::~AppLineEdit() {}

void AppLineEdit::updateTextColorStyleSheet() {
    if (this->text().isEmpty()) {
        this->setStyleSheet("QLineEdit { color: gray; }");
    } else {
        this->setStyleSheet("QLineEdit { color: white; }");
    }
}
