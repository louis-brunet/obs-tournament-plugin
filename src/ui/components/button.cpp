#include "button.hpp"

void AppButton::init(Style style, bool retainSizeWhenHidden)
{
    switch (style) {
    case Filled:
        // keep default styles
        break;

    case Transparent:
        this->setStyleSheet("QPushButton {"
                            "background-color: transparent;"
                            "}");
        break;
    }

    if (retainSizeWhenHidden) {
        auto sizePolicy = this->sizePolicy();
        sizePolicy.setRetainSizeWhenHidden(true);
        this->setSizePolicy(sizePolicy);
    }

    this->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
}

AppButton::AppButton(const char *buttonText, const QIcon &icon, Style style,
                     bool retainSizeWhenHidden)
    : QPushButton(icon, buttonText)
{
    this->init(style, retainSizeWhenHidden);
}

AppButton::AppButton(const char *buttonText, Style style,
                     bool retainSizeWhenHidden)
    : QPushButton(buttonText)
{
    this->init(style, retainSizeWhenHidden);
}

AppButton::~AppButton() {}
