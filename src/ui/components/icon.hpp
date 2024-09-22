#pragma once

#include <QIcon>

class AppIcon : public QIcon {
    // Q_OBJECT;
public:
    enum Type {
        Copy,
        Delete,
    };

    static std::string typeToFilePath(Type type);

    AppIcon(Type type);
    ~AppIcon();

private:
    AppIcon(const char *iconFilePath);
};
