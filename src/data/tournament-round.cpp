#include "tournament-round.hpp"
#include "src/data/data-helpers.hpp"

TournamentRound::TournamentRound()
{
	// TODO?
}

TournamentRound::~TournamentRound()
{
	// TODO?
}

void TournamentRound::load(obs_data_t *data)
{
	this->_name = ObsDataHelpers::getString(data, "name");

	ObsDataHelpers::iterateArray(
		data, "matches",
		[this](obs_data_t *matchData, unsigned long matchIndex) {
            UNUSED_PARAMETER(matchIndex);

			auto match = std::make_shared<Match>();
			match->load(matchData);
			this->_matches.push_back(match);
		});
}
