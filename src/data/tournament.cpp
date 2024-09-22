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
	this->_type = ObsDataHelpers::getEnum<Tournament::Type>(
		data, "type", Tournament::Type::Unknown);

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

void Tournament::save(obs_data_t *data) const
{
	obs_data_set_string(data, "name", this->_name.c_str());
	obs_data_set_int(data, "type", this->_type);

	ObsDataHelpers::saveArray<std::shared_ptr<Player>>(
		data, "players", this->_players,
		[](auto item, auto itemData) { item->save(itemData); });

	ObsDataHelpers::saveArray<std::shared_ptr<TournamentRound>>(
		data, "rounds", this->_rounds,
		[](auto item, auto itemData) { item->save(itemData); });
}

std::string Tournament::name() const
{
	return this->_name;
}

void Tournament::setName(const char *name)
{
	this->_name = name;
}

std::vector<std::shared_ptr<Player>> &Tournament::players()
{
	return this->_players;
}

void Tournament::setPlayers(std::vector<std::shared_ptr<Player>> &&__players)
{
	this->_players = __players;
}

Tournament::Type Tournament::type() const
{
	return this->_type;
}

void Tournament::setType(Tournament::Type __type)
{
	this->_type = __type;
}

std::vector<std::shared_ptr<TournamentRound>> &Tournament::rounds()
{
	return this->_rounds;
}
