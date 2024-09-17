#include "tournament-reference.hpp"

#include "src/model/plugin-data.hpp"
#include "src/model/tournament.hpp"

Tournament *TournamentReference::tournament() const
{
	if (!pluginData) {
		return nullptr;
	}

	if (this->tournamentIndex < 0 ||
	    (unsigned long)this->tournamentIndex >=
		    pluginData->tournaments.size()) {
		return nullptr;
	}

	return pluginData->tournaments.at((unsigned long)this->tournamentIndex);
}

void TournamentReference::save(obs_data_t *dataObj) const {
    obs_data_set_int(dataObj, "tournamentIndex", this->tournamentIndex);
}

void TournamentReference::load(obs_data_t *dataObj) {
    obs_data_set_default_int(dataObj, "tournamentIndex", -1);
    this->tournamentIndex = obs_data_get_int(dataObj, "tournamentIndex");
}
