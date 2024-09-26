#pragma once

#include <QPushButton>

class AppButton : public QPushButton {
    Q_OBJECT;

public:
    enum Style {
        Filled,
        Transparent,
    };

    AppButton(const char *buttonText, Style style = Style::Filled,
              bool retainSizeWhenHidden = false);

    // FIXME: this constructor with icon creates memory leaks reported by OBS????
    AppButton(const char *buttonText, const QIcon &icon,
              Style style = Style::Filled, bool retainSizeWhenHidden = false);
    ~AppButton();

private:
    void init(Style style, bool retainSizeWhenHidden);
};
