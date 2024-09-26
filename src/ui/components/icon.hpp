#pragma once

#include <QIcon>
#include <qcolor.h>

class AppIcon : public QIcon {
    // Q_OBJECT;
public:
    enum Type {
        Add,
        ArrowDownward,
        ArrowUpward,
        Copy,
        Delete,
        KeyboardArrowDown,
        KeyboardArrowUp,
    };

    // RGBA
    enum Color {
        White = (unsigned long long)0xffffffff,
        Faded = 0xffffff66,
    };

    static std::string typeToFilePath(Type type);

    AppIcon(const Type &type);
    AppIcon(const Type &type, const Color &fillColor,
            const QColor &maskColor = QColor(0, 0, 0, 0));
    ~AppIcon();

private:
    AppIcon(const char *iconFilePath, const QColor &fillColor,
            const QColor &maskColor);
    AppIcon(const char *iconFilePath);
};
