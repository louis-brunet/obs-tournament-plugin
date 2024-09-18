#include "tournament.hpp"
#include "src/model/plugin-data-object-helpers.hpp"
#include "src/plugin-support.h"
#include <obs.hpp>

Tournament::Tournament(const Tournament::Type _type,
		       // std::vector<std::unique_ptr<Player>> &&_players,
		       std::vector<Player *> &&_players,
		       TournamentReference _reference)
	// Tournament::Tournament(Tournament::Type _type,
	// 		       const std::vector<Player *> &_players)
	: players(_players),
	  type(_type),
	  reference(_reference)
{
}

Tournament::~Tournament() {}

// Tournament *Tournament::load(obs_data_t *dataObj)
// {
// 	obs_data_set_default_int(dataObj, "type",
// 				 TournamentType::CustomKnockoutTournament);
// 	auto type = (Tournament::Type)obs_data_get_int(dataObj, "type");
//
// 	auto tournament = new Tournament(type);
//
// 	OBSDataArrayAutoRelease defaultPlayersDataArray =
// 		obs_data_array_create();
// 	obs_data_set_default_array(dataObj, "players", defaultPlayersDataArray);
// 	OBSDataArrayAutoRelease playersDataArray =
// 		obs_data_get_array(dataObj, "players");
//
// 	for (unsigned int playerIndex = 0;
// 	     playerIndex < obs_data_array_count(playersDataArray);
// 	     playerIndex++) {
// 		OBSData playerDataObj =
// 			obs_data_array_item(playersDataArray, playerIndex);
//         auto player = Player::load(playerDataObj);
// 		tournament->players.push_back(player);
// 	}
//
// 	return tournament;
// }

Tournament::Type Tournament::loadType(obs_data_t *dataObj)
{
	obs_data_set_default_int(
		dataObj, "type",
		Tournament::Type::CustomKnockoutTournamentType);
	return (Tournament::Type)obs_data_get_int(dataObj, "type");
}

void Tournament::load(obs_data_t *dataObj)
{
	this->type = this->loadType(dataObj);
	obs_log(LOG_INFO, "[Tournament::load] loaded type %d", this->type);

	// std::unique_ptr<Player> p;
	// Player *p();
	// p->load(dataObj);
	// std::vector<Player *> pl= {};
	// CustomKnockoutTournament t(pl);
	// t.load(dataObj);

	// auto tournament = new Tournament(type);
	this->players.clear();
	// TournamentPluginDataObjectHelpers::loadArray<Player>(
	// 	dataObj, "players", this->players, Player::loadStatic);
	TournamentPluginDataObjectHelpers::iterateArray(
		dataObj, "players",
		[this](obs_data_t *playerDataObj, unsigned long playerIndex) {
			UNUSED_PARAMETER(playerIndex);

			// std::unique_ptr<Player> p;
			auto p = new Player();
			this->players.push_back(p);
			p->load(playerDataObj);
			// this->players.push_back(Player::loadStatic(playerDataObj));

			// auto match = new TournamentMatch();
			// this->matches.push_back(match);
			// match->load(matchDataObj);
		});

	this->matches.clear();
	TournamentPluginDataObjectHelpers::iterateArray(
		dataObj, "matches",
		[this](obs_data_t *matchDataObj, unsigned long matchIndex) {
			UNUSED_PARAMETER(matchIndex);

			MatchReference matchReference(this->reference,
						      (long long)matchIndex);
			// MatchReference matchReference { .tournamentReference = this->reference, .matchIndex = matchIndex};

			auto match = new TournamentMatch(matchReference);
			this->matches.push_back(match);
			match->load(matchDataObj);

			// this->matches.push_back(TournamentMatch::loadStatic(
			// 	matchDataObj, tournamentIndex));

			// auto match = new TournamentMatch();
			// this->matches.push_back(match);
			// match->load(matchDataObj);
		});
	// };
	// TournamentPluginDataObjectHelpers::loadArray<TournamentMatch>(
	// 	dataObj, "matches", this->matches, TournamentMatch::loadStatic);
}

void Tournament::save(obs_data_t *dataObj) const
{
	obs_data_set_int(dataObj, "type", this->type);

	TournamentPluginDataObjectHelpers::saveArray<Player>(dataObj, "players",
							     this->players);
	TournamentPluginDataObjectHelpers::saveArray<TournamentMatch>(
		dataObj, "matches", this->matches);
}

std::vector<PlayerReference> Tournament::playerReferences()
{
	std::vector<PlayerReference> references;

	for (unsigned long playerIndex = 0; playerIndex < this->players.size();
	     playerIndex++) {
		references.push_back(PlayerReference(this->reference,
						     (long long)playerIndex));
	}

	return references;
}

std::vector<MatchReference> Tournament::matchReferences()
{
	std::vector<MatchReference> references;

	for (unsigned long matchIndex = 0; matchIndex < this->matches.size();
	     matchIndex++) {
		references.push_back(
			MatchReference(this->reference, (long long)matchIndex));
	}

	return references;
}

// Tournament *Tournament::loadStatic(obs_data_t *dataObj)
// {
// 	auto type = Tournament::loadType(dataObj);
//
// 	Tournament *tournament;
// 	switch (type) {
// 	case Tournament::Type::SingleEliminationKnockoutTournamentType: {
// 		throw  std::runtime_error(
// 			"TODO: single elim knockout loadStatic");
// 		break;
// 	}
//
// 	case Tournament::Type::CustomKnockoutTournamentType: {
// 		// tournament = new CustomKnockoutTournament();
// 		tournament = CustomKnockoutTournament::loadStatic(dataObj);
// 		break;
// 	}
//
// 	default: {
// 		throw  std::runtime_error(
// 			"loadStatic: unrecognized tournament type");
// 		break;
// 	}
// 	}
//
// 	// tournament->load(dataObj);
// 	return tournament;
// }
