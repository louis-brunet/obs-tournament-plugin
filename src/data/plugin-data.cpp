#include "plugin-data.hpp"
#include <memory>
#include <obs.hpp>
#include <stdexcept>

// TournamentPluginData *pluginData = nullptr;
// auto pluginData = std::unique_ptr<TournamentPluginData>(nullptr);
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
	OBSDataArrayAutoRelease tournamentsDataArray =
		obs_data_get_array(dataObj, "tournaments");
	if (tournamentsDataArray) {
		for (unsigned int index = 0;
		     index < obs_data_array_count(tournamentsDataArray);
		     index++) {
			const OBSDataAutoRelease itemDataObj =
				obs_data_array_item(tournamentsDataArray,
						    index);

			auto tournament = std::make_shared<Tournament>();
				// std::shared_ptr<Tournament>(new Tournament());
            auto tournamentReference = TournamentReference(index);
            tournament->load(itemDataObj, tournamentReference);

			this->tournaments.push_back(tournament);

			// // this->tournaments.push_back(std::move(tournament));
			// // this->tournaments.push_back(new Tournament());
			// auto t = this->tournaments[0]->rounds();
			// // ...
		}
	}
}

void TournamentPluginData::saveSettings(obs_data_t *dataObj) {

    UNUSED_PARAMETER(dataObj);
    // throw std::runtime_error("TODO TournamentPluginData::saveSettings(obs_data_t*)");
}

std::string TournamentPluginData::toJson() {
    OBSDataAutoRelease data = obs_data_create();
    this->saveSettings(data);
    return obs_data_get_json_pretty(data);
}
