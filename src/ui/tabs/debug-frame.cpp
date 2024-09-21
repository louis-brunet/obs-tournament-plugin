#include "debug-frame.hpp"
#include "src/model/plugin-data.hpp"
#include "src/plugin-support.h"
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <obs-frontend-api.h>
#include <obs.h>
#include <obs.hpp>

DebugFrame::DebugFrame(std::function<void()> onResetDataCallback) : QFrame()
{
	auto frameLayout = new QVBoxLayout();

	auto groupBox = new QGroupBox("DEBUG");
	auto groupBoxLayout = new QHBoxLayout();
	groupBox->setLayout(groupBoxLayout);
	frameLayout->addWidget(groupBox);

	auto logDataButton = new QPushButton("log data");
	groupBoxLayout->addWidget(logDataButton, 0);
	this->connect(logDataButton, &QPushButton::clicked, []() {
		obs_log(LOG_INFO, "Plugin data:\n%s",
			pluginData->toJson().c_str());
	});

	auto clearDataButton = new QPushButton("clear data");
	groupBoxLayout->addWidget(clearDataButton, 0);
	this->connect(clearDataButton, &QPushButton::clicked,
		      [this, onResetDataCallback]() {
			      this->clearData();
			      onResetDataCallback();
		      });

	auto testButton = new QPushButton("test scenes");
	groupBoxLayout->addWidget(testButton, 0);
	this->connect(testButton, &QPushButton::clicked, []() {
		// 	// obs_frontend_sour
		// 	// OBSSourceAutoRelease d =ob ;
		// 	// struct obs_frontend_source_list a;
		// 	auto a = new obs_frontend_source_list();
		// 	obs_frontend_get_scenes(a);
		// 	for (unsigned long i = 0; i < a->sources.num; i++) {
		// 		auto source = a->sources.array[i];
		//            // (void)source;
		//
		// 		// auto c = (std::string) "Source name : " + obs_source_get_name(source);
		//
		// 		// char **scenes = obs_frontend_get_scene_names();
		// 		// char **temp = scenes;
		// 		// while (*temp) {
		// 		// 	const char *name = *temp;
		// 		//
		// 		// 	// ui->scenes->addItem(name);
		// 		// 	// ui->noMatchSwitchScene->addItem(name);
		// 		//
		// 		// 	temp++;
		// 		// }
		//
		// 		// OBSSceneAutoRelease scene = obs_scene_from_source(source);
		//
		// 		// auto sceneNames = obs_frontend_get_scene_names();
		//
		// 		// auto g = scene.Get();
		//
		// 		// for (auto d:sceneNames) {}
		//
		//
		//            auto sourceName = obs_source_get_name(source);
		//            // obs_source
		// 		obs_log(LOG_INFO, "Source name: %s",
		// 			sourceName);
		//
		//            // obs_sceneitem_get_source
		//            // obs_scene_enum_items(obs_scene_t *scene, bool (*callback)(obs_scene_t *, obs_sceneitem_t *, void *), void *param)
		// 	}
		// 	obs_frontend_source_list_free(a);

		struct obs_frontend_source_list sceneList = {};
		obs_frontend_get_scenes(&sceneList);

		auto sceneEnumItemsCallback = [](obs_scene_t *,
						 obs_sceneitem_t *sceneItem,
						 void *callbackData) -> bool {
			auto *itemSource = obs_sceneitem_get_source(sceneItem);
                // auto sourceId = obs_source_get_id(itemSource);
                // auto k = obs_sourc();
                // auto h = obs_source_get_settings(itemSource);
			auto sourceName = obs_source_get_name(itemSource);
			obs_log(LOG_INFO,
				"[] sourceName='%s'",
				sourceName);
            // auto t = obs_source_get_type(itemSource);
            //     auto u = obssourcein(itemSource);

            // bool isText = obs_source_get_type(itemSource);
			UNUSED_PARAMETER(callbackData);
			// auto *testTextSourceComboPtr =
			// 	reinterpret_cast<QComboBox *>(callbackData);
			// testTextSourceComboPtr->addItem(sourceName,
			// 				QByteArray(sourceName));
			// obs_log(LOG_INFO, "[] added '%s'", sourceName);

			return true;
		};

		for (size_t idx = 0; idx < sceneList.sources.num; idx++) {
			auto *sceneSource = sceneList.sources.array[idx];
			auto sourceName = obs_source_get_name(sceneSource);
			obs_log(LOG_INFO, "[] scene name: %s", sourceName);
            OBSSceneAutoRelease scene = obs_scene_from_source(sceneSource);
			// auto *scene = obs_get_scene_by_name(sourceName);

			obs_scene_enum_items(scene, sceneEnumItemsCallback,
					     nullptr);
			// testTextSourceCombo);

			// obs_scene_release(scene);
		}
		obs_frontend_source_list_free(&sceneList);
	});

	this->setLayout(frameLayout);
}

DebugFrame::~DebugFrame() {}

void DebugFrame::clearData()
{
	if (pluginData) {
		auto jsonData = pluginData->toJson();
		obs_log(LOG_INFO,
			"[DebugFrame::clearData] deleting plugin data, current data was: %s",
			jsonData.c_str());
		// pluginData->clearData();
		delete pluginData;
	}
	pluginData = new TournamentPluginData();
	obs_log(LOG_INFO, "[DebugFrame::clearData] plugin data is now: %s",
		pluginData->toJson().c_str());
}
