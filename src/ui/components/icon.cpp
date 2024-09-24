#include "icon.hpp"
#include <obs-module.h>

AppIcon::AppIcon(const char *iconFilePath) : QIcon(iconFilePath) {}

AppIcon::AppIcon(Type type) : AppIcon(AppIcon::typeToFilePath(type).c_str()) {}

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
