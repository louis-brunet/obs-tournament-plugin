#include "icon.hpp"
#include <obs-module.h>
#include <QPixmap>
#include <qbitmap.h>
#include <qcolor.h>

static QColor rgbaQColor(unsigned int rgba)
{
    auto r = (unsigned char)(((unsigned int)rgba) >> 24);
    auto g = (unsigned char)(((unsigned int)rgba) >> 16);
    auto b = (unsigned char)(((unsigned int)rgba) >> 8);
    auto a = (unsigned char)(((unsigned int)rgba));
    return QColor(r, g, b, a);
}

static QPixmap iconPixmap(const char *filePath, const QColor &fillColor,
                          const QColor &maskColor)
{
    QPixmap pixmap(filePath);

    // if (fillColor) {
    QBitmap mask = pixmap.createMaskFromColor(maskColor);
    pixmap.fill(fillColor);
    pixmap.setMask(mask);
    // }

    return pixmap;
}

AppIcon::AppIcon(const char *iconFilePath) : QIcon(iconFilePath) {}

AppIcon::AppIcon(const char *iconFilePath, const QColor &fillColor,
                 const QColor &maskColor)
    : QIcon(iconPixmap(iconFilePath, fillColor, maskColor))
{
}

AppIcon::AppIcon(const Type &type, const Color &fillColor,
                 const QColor &maskColor)
    : AppIcon(AppIcon::typeToFilePath(type).c_str(), rgbaQColor(fillColor),
              maskColor)
{
}

AppIcon::AppIcon(const Type &type)
    : AppIcon(AppIcon::typeToFilePath(type).c_str())
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
    case KeyboardArrowDown:
        iconPath += "keyboard_arrow_down.svg";
        break;
    case KeyboardArrowUp:
        iconPath += "keyboard_arrow_up.svg";
        break;
    }

    return obs_module_file(iconPath.c_str());
}
