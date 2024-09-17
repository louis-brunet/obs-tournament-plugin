#include "tournament-match.hpp"
#include "src/plugin-support.h"
#include <obs.hpp>

TournamentMatch::TournamentMatch(MatchReference __reference)
	: _reference(__reference)
// TournamentMatch::TournamentMatch(const char *__matchLabel,
// 				 TournamentMatchParticipant *player1,
// 				 TournamentMatchParticipant *player2)
// : _matchLabel(__matchLabel),
//   _participant1(player1),
//   _participant2(player2)
{
	// this->participants[0] = player1;
	// this->participants[1] = player2;
	// this->_matchLabel = __matchLabel;
}

TournamentMatch::~TournamentMatch() {}

TournamentMatch *TournamentMatch::loadStatic(obs_data_t *dataObj,
					     long long tournamentIndex)
//, ........TODO tournament? tournamentIndex ??????? should probably redo tournament loading to use indices rather than pointers....)
{
	UNUSED_PARAMETER(tournamentIndex);

	// TODO: ?
	// auto tou
	// auto tm = new TournamentMatch();
	// tm->load(dataObj);
	// return tm;
}

void TournamentMatch::load(obs_data_t *dataObj)
{
	obs_log(LOG_INFO, "[TournamentMatch::load] loading matchLabel");
	this->_matchLabel = obs_data_get_string(dataObj, "matchLabel");
	obs_log(LOG_INFO, "[TournamentMatch::load] matchLabel=%s",
		this->_matchLabel.c_str());

	obs_log(LOG_INFO, "[TournamentMatch::load] loading participant1");
	OBSDataAutoRelease player1DataObj =
		obs_data_get_obj(dataObj, "player1");
	// this->participants[0] =
	this->_participant1 = TournamentMatchParticipant::loadStatic(
		player1DataObj, this->_reference);
	// this->_participant1 = new TournamentMatchParticipant(this->re);

	obs_log(LOG_INFO, "[TournamentMatch::load] loading participant2");
	OBSDataAutoRelease player2DataObj =
		obs_data_get_obj(dataObj, "player2");
	// this->participants[1] =
	this->_participant2 =
		TournamentMatchParticipant::loadStatic(player2DataObj);
}

void TournamentMatch::save(obs_data_t *dataObj) const
{
	obs_log(LOG_INFO, "[TournamentMatch::save] saving player1");
	OBSDataAutoRelease player1DataObj = obs_data_create();
	// this->participants[0]->save(player1DataObj);
	this->_participant1->save(player1DataObj);
	obs_data_set_obj(dataObj, "player1", player1DataObj);

	obs_log(LOG_INFO, "[TournamentMatch::save] saving player2");
	OBSDataAutoRelease player2DataObj = obs_data_create();
	// this->participants[1]->save(player2DataObj);
	this->_participant2->save(player2DataObj);
	obs_data_set_obj(dataObj, "player2", player2DataObj);

	obs_log(LOG_INFO, "[TournamentMatch::save] saving matchLabel");
	obs_data_set_string(dataObj, "matchLabel", this->_matchLabel.c_str());
}

std::string TournamentMatch::matchLabel() const
{
	return this->_matchLabel;
}

TournamentMatchParticipant *TournamentMatch::participant1()
{
	return this->_participant1;
	// return this->participants[0];
}

TournamentMatchParticipant *TournamentMatch::participant2()
{
	return this->participants[1];
}

void TournamentMatch::setParticipant1(TournamentMatchParticipant *participant)
{
	this->participants[0] = participant;
}

void TournamentMatch::setParticipant2(TournamentMatchParticipant *participant)
{
	this->participants[1] = participant;
}
