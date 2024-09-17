#include "plugin-main.hpp"
#include "plugin-support.h"
#include "src/model/plugin-data.hpp"
#include "src/ui/dialogs/plugin-dialog.hpp"
#include "version.h"

// #include <obs.h>
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

OBS_DECLARE_MODULE()
OBS_MODULE_AUTHOR("Louis Brunet");
OBS_MODULE_USE_DEFAULT_LOCALE(PLUGIN_NAME, "en-US")

static void frontend_save_load(obs_data_t *saveData, bool saving,
			       void *privateData)
{
	UNUSED_PARAMETER(privateData);

	if (!pluginData) {
		return;
	}

	if (saving) {
		obs_log(LOG_INFO, "Saving");
		OBSDataAutoRelease settingsData = obs_data_create();
		obs_data_set_obj(saveData, PLUGIN_NAME, settingsData);
		pluginData->saveSettings(settingsData);
		obs_data_set_obj(saveData, PLUGIN_NAME, settingsData);

		obs_log(LOG_INFO, "Saved settings:\n%s",
			obs_data_get_json_pretty(settingsData));
		// OBSDataAutoRelease savedSettings =
		// 	obs_data_get_obj(saveData, PLUGIN_NAME);
		// obs_log(LOG_INFO, "Saved settings:\n%s",
		// 	obs_data_get_json_pretty(savedSettings));
	} else {
		obs_log(LOG_INFO, "Loading save data");
		// obs_log(LOG_INFO, "All saveData:\n%s",
		// 	obs_data_get_json_pretty(saveData));

		OBSDataAutoRelease settingsData =
			obs_data_get_obj(saveData, PLUGIN_NAME);
		if (!settingsData) {
			obs_log(LOG_INFO, "Loading - save data does not exist");
			settingsData = obs_data_create();
		}
        pluginData->loadSettings(settingsData);
		obs_log(LOG_INFO, "Loading - save data exists:\n%s",
			obs_data_get_json_pretty(settingsData));
		obs_log(LOG_INFO, "Loaded plugin data - %s",
			pluginData->toJson().c_str());
	}
}

bool obs_module_load(void)
{
	obs_log(LOG_INFO, "[%s] loaded version %s", PLUGIN_NAME,
		PROJECT_VERSION);
	initTournamentPluginData();

	auto *action = (QAction *)obs_frontend_add_tools_menu_qaction(
		obs_module_text("TournamentPluginName"));
	auto cb = [] {
		obs_frontend_push_ui_translation(obs_module_get_string);

		try {
			auto pluginDialog = new TournamentPluginDialog();
			// std::string(PLUGIN_VERSION),
			// (QMainWindow *)obs_frontend_get_main_window());
			// auto pluginDialog = TournamentPluginDialog::getInstance();
			// pluginDialog->setAttribute(Qt::WA_DeleteOnClose);
			pluginDialog->show();
		} catch (const std::exception &e) {
			obs_log(LOG_ERROR,
				"Error during plugin dialog initialization: %s",
				e.what());
		}
		obs_frontend_pop_ui_translation();
	};
	QAction::connect(action, &QAction::triggered, cb);

	obs_frontend_add_save_callback(frontend_save_load,
				       nullptr); //pluginData);

	// obs_frontend_add_event_callback(frontend_event, nullptr);
	// signal_handler_connect(obs_get_signal_handler(), "source_rename",
	// 		       source_rename, nullptr);

	// transition_table_hotkey = obs_hotkey_pair_register_frontend(
	// 	"transition-table.enable",
	// 	obs_module_text("TransitionTable.Enable"),
	// 	"transition-table.disable",
	// 	obs_module_text("TransitionTable.Disable"), enable_hotkey,
	// 	disable_hotkey, nullptr, nullptr);
	// auto ph = obs_get_proc_handler();
	// proc_handler_add(
	// 	ph,
	// 	"void get_transition_table_transition(string from_scene, string to_scene, out string transition, out int duration)",
	// 	proc_get_transition, nullptr);

	// {
	// 	// auto testFileName = obs_module_file("locale/en-US.ini");
	// 	// string testFileString;
	// 	// auto relativeFileName = "settings.json";
	// 	// auto testFileNameCStr = obs_module_file(relativeFileName);
	// 	// if (!testFileNameCStr) {
	// 	// 	obs_log(LOG_INFO,
	// 	// 		"COULD NOT FIND MODULE FILE, TRYING TO CREATE",
	// 	// 		testFileString.c_str());
	// 	// 	auto moduleDataDirectory = obs_module_file("");
	// 	// 	testFileString = (string)moduleDataDirectory + "/" +
	// 	// 			 relativeFileName;
	// 	// 	bfree(moduleDataDirectory);
	// 	//
	// 	// 	// obs_file
	// 	// 	// obs_data_t* p;
	// 	// 	// obs_set_private_data();
	// 	//
	// 	// 	// fstream testOutStream;
	// 	// 	// testOutStream.open(testFileString, ios::out);
	// 	// 	// testOutStream << "hello\n";
	// 	// 	// // testOutStream.flush();
	// 	// 	// testOutStream.close();
	// 	//
	// 	// } else {
	// 	// 	testFileString = string(testFileNameCStr);
	// 	// }
	// 	// bfree(testFileNameCStr);
	//
	// 	auto moduleConfigDirectory = obs_module_config_path("");
	// 	std::filesystem::create_directory(moduleConfigDirectory);
	// 	bfree(moduleConfigDirectory);
	//
	// 	auto configPathCStr = obs_module_config_path("settings.json");
	// 	string testFileString = configPathCStr;
	// 	obs_log(LOG_INFO, "TEST FILE PATH IS: %s\nCONFIG PATH IS: %s",
	// 		testFileString.c_str(), configPathCStr);
	// 	bfree(configPathCStr);
	//
	// 	auto testData = obs_data_create();
	// 	obs_data_set_string(testData, "someKey", "someVal");
	// 	auto json = obs_data_get_json_pretty(testData);
	// 	if (json) {
	// 		ofstream configFileStream(testFileString);
	// 		configFileStream << json;
	// 		configFileStream.close();
	// 	}
	// 	// auto isSaved = obs_data_save_json_pretty(testData, testFileString.c_str());
	// 	obs_log(LOG_INFO, "saved json data to '%s'", testFileString.c_str());
	// 	// auto jsonData =
	// 	// 	obs_data_create_from_json_file(testFileString.c_str());
	// 	// obs_log(LOG_INFO, "JSON data ptr is %p", jsonData);
	// }

	return true;
}

void obs_module_post_load(void)
{
	// vendor = obs_websocket_register_vendor("transition-table");
	// if (!vendor)
	// 	return;
	// obs_websocket_vendor_register_request(vendor, "get_transition",
	// 				      vendor_get_transition, nullptr);
	// obs_websocket_vendor_register_request(vendor, "set_transition",
	// 				      vendor_set_transition, nullptr);
	// obs_websocket_vendor_register_request(vendor, "get_table",
	// 				      vendor_get_table, nullptr);
}

void obs_module_unload(void)
{
	freeTournamentPluginData();
	// obs_hotkey_pair_unregister(transition_table_hotkey);
	// // obs_frontend_remove_save_callback(frontend_save_load, nullptr);
	// // obs_frontend_remove_event_callback(frontend_event, nullptr);
	// // signal_handler_disconnect(obs_get_signal_handler(), "source_rename",
	// // 			  source_rename, nullptr);
	// transition_table.clear();
}

MODULE_EXPORT const char *obs_module_description(void)
{
	return obs_module_text("Description");
}

MODULE_EXPORT const char *obs_module_name(void)
{
	return obs_module_text("TournamentPluginName");
}
