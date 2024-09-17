#include "line-edit.hpp"

AppLineEdit::AppLineEdit()
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
