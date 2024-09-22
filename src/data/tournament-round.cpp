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

void TournamentRound::save(obs_data_t *data) const
{
	obs_data_set_string(data, "name", this->_name.c_str());

	ObsDataHelpers::saveArray<std::shared_ptr<Match>>(
		data, "matches", this->_matches,
		[](auto match, auto matchData) { match->save(matchData); });
}

std::string TournamentRound::name() const
{
	return this->_name;
}

std::vector<std::shared_ptr<Match>> &TournamentRound::matches()
{
	return this->_matches;
}
