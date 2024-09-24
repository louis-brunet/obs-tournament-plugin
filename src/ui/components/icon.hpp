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
    };

    static std::string typeToFilePath(Type type);

    AppIcon(Type type, const QColor *fillColor = nullptr);
    ~AppIcon();

private:
    AppIcon(const char *iconFilePath, const QColor *fillColor);
};
