#include "icon.hpp"
#include <obs-module.h>
#include <stdexcept>

AppIcon::AppIcon(const char *iconFilePath) : QIcon(iconFilePath) {}

AppIcon::AppIcon(Type type) : AppIcon(AppIcon::typeToFilePath(type).c_str()) {}

AppIcon::~AppIcon() {}

std::string AppIcon::typeToFilePath(Type type)
{
	std::string iconPath = "icons/";

	switch (type) {
	case Copy:
		iconPath += "content_copy.svg";
		break;
	case Delete:
		iconPath += "delete.svg";
		break;
	default:
		throw std::runtime_error("[AppIcon::typeToFilePath] unhandled enum variant");
	}

	return obs_module_file(iconPath.c_str());
}
