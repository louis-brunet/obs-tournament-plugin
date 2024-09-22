#include "plugin-support.h"
#include "src/data/plugin-data.hpp"
#include "src/logger.hpp"
#include "src/ui/dialogs/plugin-dialog.hpp"

#include <obs.hpp>
#include <obs-module.h>
#include <obs-frontend-api.h>
#include <obs-config.h>
#include <obs-data.h>

#include <QAction>
#include <QCheckBox>
#include <QComboBox>
#include <QCompleter>

#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <qmainwindow.h>

OBS_DECLARE_MODULE()
OBS_MODULE_AUTHOR("Louis Brunet");
OBS_MODULE_USE_DEFAULT_LOCALE(PLUGIN_NAME, "en-US")

using namespace Logger;

static void frontend_save_load(obs_data_t *saveData, bool saving,
			       void *privateData)
{
	UNUSED_PARAMETER(privateData);
	// UNUSED_PARAMETER(saveData);
	// UNUSED_PARAMETER(saving);

	if (!pluginData) {
		return;
	}

	if (saving) {
		log("Saving");

		OBSDataAutoRelease settingsData = obs_data_create();
		obs_data_set_obj(saveData, PLUGIN_NAME, settingsData);
		try {
			pluginData->saveSettings(settingsData);
		} catch (const std::exception &e) {
			log("Error during saveSettings: %s", e.what());
			throw e;
		}
		obs_data_set_obj(saveData, PLUGIN_NAME, settingsData);

		log("Saved settings:\n%s",
		    obs_data_get_json_pretty(settingsData));
	} else {
		log("Loading save data");
		// log(LOG_DEBUG, "All saveData:\n%s",
		// 	obs_data_get_json_pretty(saveData));

		OBSDataAutoRelease settingsData =
			obs_data_get_obj(saveData, PLUGIN_NAME);
		if (!settingsData) {
			log("Loading - save data does not exist");
			settingsData = obs_data_create();
		} else {
			log("Loading - save data exists:\n%s",
			    obs_data_get_json_pretty(settingsData));
		}

		try {
			pluginData->loadSettings(settingsData);
		} catch (const std::exception &e) {
			log("Error during loadSettings: %s", e.what());
			throw e;
		}

		log("Loaded plugin data - %s", pluginData->toJson().c_str());
	}
}

bool obs_module_load(void)
{
	log("loaded version %s for %s", PLUGIN_VERSION, PLUGIN_NAME);

	initTournamentPluginData();

	auto *action = (QAction *)obs_frontend_add_tools_menu_qaction(
		obs_module_text("plugin.name"));
	auto cb = [] {
		obs_frontend_push_ui_translation(obs_module_get_string);

		try {
			auto pluginDialog = new PluginDialog(nullptr);
			pluginDialog->show();
		} catch (const std::exception &e) {
			log("Error during plugin dialog initialization: %s",
			    e.what());
			throw e;
		}
		obs_frontend_pop_ui_translation();
	};
	QAction::connect(action, &QAction::triggered, cb);

	obs_frontend_add_save_callback(frontend_save_load,
				       nullptr); //pluginData);

	return true;
}

void obs_module_post_load(void) {}

void obs_module_unload(void)
{
	freeTournamentPluginData();
	obs_frontend_remove_save_callback(frontend_save_load, nullptr);
}

MODULE_EXPORT const char *obs_module_description(void)
{
	return obs_module_text("plugin.description");
}

MODULE_EXPORT const char *obs_module_name(void)
{
	return obs_module_text("plugin.name");
}
