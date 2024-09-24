#pragma once

#include <QPushButton>

class AppButton : public QPushButton {
    Q_OBJECT;

public:
    enum Style {
        Filled,
        Transparent,
    };

    AppButton(const char *buttonText, Style style = Style::Filled, bool retainSizeWhenHidden = false);
    AppButton(const char *buttonText, const QIcon &icon, Style style = Style::Filled,
              bool retainSizeWhenHidden = false);
    ~AppButton() = default;

private:
    void init(Style style, bool retainSizeWhenHidden);
};
