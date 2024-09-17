#include "plugin-data.hpp"
#include "src/model/custom-knockout-tournament.hpp"
#include "src/model/plugin-data-object-helpers.hpp"
#include "src/model/tournament-reference.hpp"
#include <obs-data.h>
#include <obs.hpp>
#include <stdexcept>

TournamentPluginData *pluginData = nullptr;

void initTournamentPluginData()
{
	pluginData = new TournamentPluginData();
}

void freeTournamentPluginData()
{
	// TODO: any shutdown cleanup?

	delete pluginData;
	pluginData = nullptr;
}

TournamentPluginData::TournamentPluginData() {}

TournamentPluginData::~TournamentPluginData() {}

void TournamentPluginData::loadSettings(obs_data_t *dataObj)
{
	if (!dataObj) {
		return;
	}

	TournamentPluginDataObjectHelpers::iterateArray(
		dataObj, "tournaments",
		[this](obs_data_t *tournamentDataObj,
		       unsigned long tournamentIndex) {
			// auto tournament = new Tournament(tournamentIndex);
			// auto tournament = new Tournament(tournamentDataObj, tournamentIndex);
			auto type = Tournament::loadType(tournamentDataObj);

			TournamentReference reference{.tournamentIndex =
							      tournamentIndex};

			// Tournament *tournament;
			switch (type) {
			case Tournament::Type::
				SingleEliminationKnockoutTournamentType: {
				throw new std::runtime_error(
					"TODO: single elim knockout loadStatic");
				break;
			}

			case Tournament::Type::CustomKnockoutTournamentType: {
				auto t = new CustomKnockoutTournament(reference);
				this->tournaments.push_back(t);
				t->load(tournamentDataObj);
				break;
			}

			default: {
				throw new std::runtime_error(
					"loadStatic: unrecognized tournament type");
				break;
			}
			}
		});

	TournamentPluginDataObjectHelpers::loadArray<Tournament>(
		dataObj, "tournaments", this->tournaments,
		Tournament::loadStatic);
}

void TournamentPluginData::saveSettings(obs_data_t *dataObj)
{
	if (!dataObj) {
		return;
	}

	OBSDataArrayAutoRelease tournamentsDataArray = obs_data_array_create();
	for (auto tournament : this->tournaments) {
		OBSDataAutoRelease tournamentDataObj = obs_data_create();
		tournament->save(tournamentDataObj);
		obs_data_array_push_back(tournamentsDataArray,
					 tournamentDataObj);
	}
	obs_data_set_array(dataObj, "tournaments", tournamentsDataArray);
}

std::string TournamentPluginData::toJson()
{
	OBSDataAutoRelease dataObj = obs_data_create();
	this->saveSettings(dataObj);
	std::string json = obs_data_get_json_pretty(dataObj);
	return json;
}
