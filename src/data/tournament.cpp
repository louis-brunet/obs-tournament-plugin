#include "tournament.hpp"
#include "src/data/data-helpers.hpp"
#include <memory>
#include <obs.hpp>

Tournament::Tournament() {}

Tournament::~Tournament() {}

void Tournament::load(obs_data_t *data,
		      const TournamentReference &tournamentReference)
{
    UNUSED_PARAMETER(tournamentReference);

	this->_name = "";
	this->_players.clear();
	this->_rounds.clear();

	this->_name = ObsDataHelpers::getString(data, "name");

	ObsDataHelpers::iterateArray(
		data, "players",
		[this](obs_data_t *itemDataObj, unsigned long playerIndex) {
			UNUSED_PARAMETER(playerIndex);

			auto player = std::make_shared<Player>();
			player->load(itemDataObj);

			this->_players.push_back(player);
		});

	ObsDataHelpers::iterateArray(
		data, "rounds",
		[this](obs_data_t *itemDataObj, unsigned long roundIndex) {
            UNUSED_PARAMETER(roundIndex);

			auto round = std::make_shared<TournamentRound>();
			round->load(itemDataObj);
			this->_rounds.push_back(round);
		});
}
