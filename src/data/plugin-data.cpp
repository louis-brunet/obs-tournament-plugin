#include "plugin-data.hpp"
#include "src/data/data-helpers.hpp"
#include <memory>
#include <obs.hpp>

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
