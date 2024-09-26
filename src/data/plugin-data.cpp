#include "plugin-data.hpp"
#include "src/data/data-helpers.hpp"
#include "src/logger.hpp"
#include <memory>
#include <obs.h>
#include <obs.hpp>
#include <obs-frontend-api.h>

std::unique_ptr<TournamentPluginData> pluginData = nullptr;

void initTournamentPluginData()
{
    pluginData = std::make_unique<TournamentPluginData>();
}

void freeTournamentPluginData()
{
    // TODO: any shutdown cleanup?

    // delete pluginData;
    pluginData = nullptr;
}

TournamentPluginData::TournamentPluginData() {}

TournamentPluginData::~TournamentPluginData() {}

void TournamentPluginData::loadSettings(obs_data_t *dataObj)
{
    ObsDataHelpers::iterateArray(
        dataObj, "tournaments",
        [this](auto tournamentData, auto tournamentIndex) {
            auto tournament = std::make_shared<Tournament>();
            auto tournamentReference =
                TournamentReference((long long)tournamentIndex);
            tournament->load(tournamentData, tournamentReference);
            this->tournaments.push_back(tournament);
        });

    // OBSDataArrayAutoRelease tournamentsDataArray =
    // 	obs_data_get_array(dataObj, "tournaments");
    // if (tournamentsDataArray) {
    // 	for (unsigned int index = 0;
    // 	     index < obs_data_array_count(tournamentsDataArray);
    // 	     index++) {
    // 		const OBSDataAutoRelease itemDataObj =
    // 			obs_data_array_item(tournamentsDataArray,
    // 					    index);
    //
    // 		auto tournament = std::make_shared<Tournament>();
    // 		// std::shared_ptr<Tournament>(new Tournament());
    // 		auto tournamentReference = TournamentReference(index);
    // 		tournament->load(itemDataObj, tournamentReference);
    //
    // 		this->tournaments.push_back(tournament);
    //
    // 		// // this->tournaments.push_back(std::move(tournament));
    // 		// // this->tournaments.push_back(new Tournament());
    // 		// auto t = this->tournaments[0]->rounds();
    // 		// // ...
    // 	}
    // }
}

void TournamentPluginData::saveSettings(obs_data_t *dataObj)
{
    ObsDataHelpers::saveArray<std::shared_ptr<Tournament>>(
        dataObj, "tournaments", this->tournaments,
        [](auto item, auto itemData) { item->save(itemData); });
}

std::string TournamentPluginData::toJson()
{
    OBSDataAutoRelease data = obs_data_create();
    this->saveSettings(data);
    return obs_data_get_json_pretty(data);
}

static bool isTextSource(obs_source_t *source)
{
    std::string id = obs_source_get_unversioned_id(source);
    return id == "text_ft2_source";
}

static bool isImageSource(obs_source_t *source)
{
    std::string id = obs_source_get_unversioned_id(source);
    return id == "image_source";
}

std::vector<OBSWeakSource>
sources(std::function<bool(obs_source_t *)> filterCallback)
{
    struct obs_frontend_source_list sceneList = {};
    obs_frontend_get_scenes(&sceneList);

    auto sceneEnumItemsCallback = [](obs_scene_t *, obs_sceneitem_t *sceneItem,
                                     void *callbackData) -> bool {
        auto typedCallbackData =
            (std::pair<std::vector<OBSWeakSource> *,
                       std::function<bool(obs_source_t *)>> *)callbackData;
        auto weakSources = typedCallbackData->first;
        auto _filterCallback = typedCallbackData->second;
        // (std::vector<OBSWeakSourceAutoRelease> *)callbackData;

        obs_source_t *itemSource = obs_sceneitem_get_source(sceneItem);
        if (_filterCallback(itemSource)) {
            obs_weak_source_t *weakSource =
                obs_source_get_weak_source(itemSource);
            weakSources->push_back(weakSource);
        }

        return true;
    };

    std::vector<OBSWeakSource> weakSourcesResult;
    auto callbackPrivateData = std::pair(&weakSourcesResult, filterCallback);

    for (size_t idx = 0; idx < sceneList.sources.num; idx++) {
        auto *sceneSource = sceneList.sources.array[idx];
        obs_scene_t *scene = obs_scene_from_source(sceneSource);
        obs_scene_enum_items(scene, sceneEnumItemsCallback,
                             &callbackPrivateData);
    }
    obs_frontend_source_list_free(&sceneList);

    return weakSourcesResult;
}

std::vector<OBSWeakSource> TournamentPluginData::imageSources()
{
    return sources(isImageSource);
}

std::vector<OBSWeakSource> TournamentPluginData::textSources()
{
    return sources(isTextSource);
    // struct obs_frontend_source_list sceneList = {};
    // obs_frontend_get_scenes(&sceneList);
    //
    // auto sceneEnumItemsCallback = [](obs_scene_t *, obs_sceneitem_t *sceneItem,
    //                                  void *callbackData) -> bool {
    //     auto weakSources =
    //         (std::vector<OBSWeakSourceAutoRelease> *)callbackData;
    //     obs_source_t *itemSource = obs_sceneitem_get_source(sceneItem);
    //     if (isTextSource(itemSource)) {
    //         obs_weak_source_t *weakSource =
    //             obs_source_get_weak_source(itemSource);
    //         weakSources->push_back(weakSource);
    //     }
    //
    //     return true;
    // };
    //
    // std::vector<OBSWeakSourceAutoRelease> weakSourcesResult;
    //
    // for (size_t idx = 0; idx < sceneList.sources.num; idx++) {
    //     auto *sceneSource = sceneList.sources.array[idx];
    //     obs_scene_t *scene = obs_scene_from_source(sceneSource);
    //     obs_scene_enum_items(scene, sceneEnumItemsCallback, &weakSourcesResult);
    // }
    // obs_frontend_source_list_free(&sceneList);
    //
    // return weakSourcesResult;
}
