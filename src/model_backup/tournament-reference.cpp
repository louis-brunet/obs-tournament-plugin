#include "tournament-reference.hpp"

#include "src/model/plugin-data.hpp"
#include "src/model/tournament.hpp"
#include "src/plugin-support.h"

TournamentReference::TournamentReference(long long _tournamentIndex)
	: tournamentIndex(_tournamentIndex)
{
}

TournamentReference::~TournamentReference() {}

Tournament *TournamentReference::tournament() const
{
	if (!pluginData) {
		obs_log(LOG_INFO,
			"[TournamentReference::tournament] pluginData is null!");

		return nullptr;
	}

	if (this->tournamentIndex < 0 ||
	    (unsigned long)this->tournamentIndex >=
		    pluginData->tournaments.size()) {
		obs_log(LOG_INFO,
			"[TournamentReference::tournament] tournamentIndex %d is out of range [%d, %d[",
			this->tournamentIndex, 0,
			pluginData->tournaments.size());
		return nullptr;
	}

	return pluginData->tournaments.at((unsigned long)this->tournamentIndex);
}

void TournamentReference::save(obs_data_t *dataObj) const
{
	obs_data_set_int(dataObj, "tournamentIndex", this->tournamentIndex);
}

void TournamentReference::load(obs_data_t *dataObj)
{
	obs_data_set_default_int(dataObj, "tournamentIndex", -1);
	this->tournamentIndex = obs_data_get_int(dataObj, "tournamentIndex");
}
