#include "plugin-dialog.hpp"
#include <obs-module.h>
#include <qboxlayout.h>
#include <qlabel.h>

int pluginDialogWidth = 0;
int pluginDialogHeight = 0;
int pluginDialogMinWidth = 600;
int pluginDialogMinHeight = 400;

PluginDialog::PluginDialog(QMainWindow *parent)
	: BaseDialog(parent, obs_module_text("plugin.name"), pluginDialogMinWidth,
		     pluginDialogMinHeight)
{
	auto vlayout = new QVBoxLayout;
	vlayout->setContentsMargins(11, 11, 11, 11);
	vlayout->setAlignment(Qt::AlignTop);
	// vlayout->addWidget(this->tabsWidget);
	// vlayout->addLayout(bottomLayout);
	this->setLayout(vlayout);

	vlayout->addWidget(new QLabel("TODO plugin dialog"));

	if (pluginDialogWidth > pluginDialogMinWidth &&
	    pluginDialogHeight > pluginDialogMinHeight) {
		this->resize(pluginDialogWidth, pluginDialogHeight);
	}

}

PluginDialog::~PluginDialog() {}
