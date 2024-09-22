#include "match-reference.hpp"

#include "src/model/tournament-match.hpp"
#include "src/model/tournament.hpp"
#include "src/plugin-support.h"

MatchReference::MatchReference(TournamentReference _tournamentReference,
			       long long _matchIndex)
	: tournamentReference(_tournamentReference),
	  matchIndex(_matchIndex)
{
}

MatchReference::~MatchReference() {}

TournamentMatch *MatchReference::match() const
{
	auto tournament = this->tournamentReference.tournament();
	if (!tournament) {
        obs_log(LOG_INFO, "[MatchReference::match] tournament is null, tournamentIndex=%d!", this->tournamentReference.tournamentIndex);
		return nullptr;
	}

	if (this->matchIndex < 0 ||
	    (unsigned long)this->matchIndex >= tournament->matches.size()) {
		return nullptr;
	}
	return tournament->matches.at((unsigned long)this->matchIndex);
}

void MatchReference::save(obs_data_t *dataObj) const
{
	OBSDataAutoRelease tournamentData = obs_data_create();
	this->tournamentReference.save(tournamentData);
	obs_data_set_obj(dataObj, "tournamentReference", tournamentData);

	obs_data_set_int(dataObj, "matchIndex", this->matchIndex);
}

void MatchReference::load(obs_data_t *dataObj)
{
	OBSDataAutoRelease tournamentData =
		obs_data_get_obj(dataObj, "tournamentReference");
	this->tournamentReference.load(tournamentData);

	obs_data_set_default_int(dataObj, "matchIndex", -1);
	this->matchIndex = obs_data_get_int(dataObj, "matchIndex");
}
