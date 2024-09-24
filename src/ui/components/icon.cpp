#include "icon.hpp"
#include <obs-module.h>
#include <QPixmap>
#include <qbitmap.h>
#include <qcolor.h>

static QPixmap iconPixmap(const char *filePath,
                          const QColor *fillColor = nullptr,
                          const QColor &maskColor = QColor(0, 0, 0, 0))
{
    QPixmap pixmap(filePath);

    if (fillColor) {
        QBitmap mask = pixmap.createMaskFromColor(maskColor);
        pixmap.fill(*fillColor);
        pixmap.setMask(mask);
    }

    return pixmap;
}

AppIcon::AppIcon(const char *iconFilePath, const QColor *fillColor)
    : QIcon(iconPixmap(iconFilePath, fillColor))
{
}

AppIcon::AppIcon(Type type, const QColor *fillColor)
    : AppIcon(AppIcon::typeToFilePath(type).c_str(), fillColor)
{
}

AppIcon::~AppIcon() {}

std::string AppIcon::typeToFilePath(Type type)
{
    std::string iconPath = "icons/";

    switch (type) {
    case Add:
        iconPath += "add.svg";
        break;
    case Copy:
        iconPath += "content_copy.svg";
        break;
    case Delete:
        iconPath += "delete.svg";
        break;
    case ArrowDownward:
        iconPath += "arrow_downward.svg";
        break;
    case ArrowUpward:
        iconPath += "arrow_upward.svg";
        break;
    }

    return obs_module_file(iconPath.c_str());
}
