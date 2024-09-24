#include "tournament-reference.hpp"
#include "src/data/plugin-data.hpp"
#include "src/data/tournament.hpp"
#include <obs.hpp>

TournamentReference::TournamentReference(long long _tournamentIndex)
	: tournamentIndex(_tournamentIndex)
{
}

TournamentReference::~TournamentReference() {}

std::shared_ptr<Tournament> TournamentReference::tournament() const
{
	if (this->tournamentIndex < 0 ||
	    (unsigned long)this->tournamentIndex >=
		    pluginData->tournaments.size()) {
		return nullptr;
	}

	return pluginData->tournaments.at((unsigned long)this->tournamentIndex);
}

void TournamentReference::load(obs_data_t *data) {
    obs_data_set_default_int(data, "tournamentIndex", -1);
    this->tournamentIndex = obs_data_get_int(data, "tournamentIndex");
}

void TournamentReference::save(obs_data_t *data) const {
    obs_data_set_int(data, "tournamentIndex", this->tournamentIndex);
}
