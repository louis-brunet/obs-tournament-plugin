#include "tournament-match-participant.hpp"
#include "src/model/tournament-match-participant-player.hpp"
#include "src/model/tournament-match-participant-unknown.hpp"
#include "src/model/tournament-match-participant-winner-of-match.hpp"
#include "src/plugin-support.h"
#include <stdexcept>

TournamentMatchParticipant::TournamentMatchParticipant(
	TournamentMatchParticipant::Type __type)
	// TournamentMatchParticipant::Type __type, MatchReference matchReference)
	: _type(__type)
//,
// _matchReference(matchReference)
{
}

TournamentMatchParticipant::~TournamentMatchParticipant() {}

TournamentMatchParticipant *
TournamentMatchParticipant::loadStatic(obs_data_t *dataObj)
{
	if (!dataObj) {
		return nullptr;
	}

	// auto dataType = (TournamentMatchParticipant::Type)obs_data_get_int(
	// 	dataObj, "participantType");
	auto dataType = TournamentMatchParticipant::loadType(dataObj);

	obs_log(LOG_INFO,
		"[TournamentMatchParticipant::loadStatic] participantType=%d",
		dataType);
	TournamentMatchParticipant *participant;
	switch (dataType) {
	case TournamentMatchParticipant::Type::Unknown: {
		auto p = new TournamentMatchParticipantUnknown();
		p->load(dataObj);
		participant = p;

		break;
	}

	case TournamentMatchParticipant::Type::StaticPlayer: {
		auto p = new TournamentMatchParticipantPlayer();
		p->load(dataObj);
		participant = p;

		break;
	}

	case TournamentMatchParticipant::Type::WinnerOfMatch: {
		participant =
			TournamentMatchParticipantWinnerOfMatch::loadStatic(
				dataObj);
		// dataObj, matchReference);
		// auto p = new TournamentMatchParticipantWinnerOfMatch();
		// p->load(dataObj, tournament);
		// participant = p;

		break;
	}

	default:
		throw std::runtime_error("unrecognized participant type");
	}

	return participant;
}

TournamentMatchParticipant::Type TournamentMatchParticipant::type()
{
	return this->_type;
}

TournamentMatchParticipant::Type
TournamentMatchParticipant::loadType(obs_data_t *dataObj)
{
	obs_data_set_default_int(dataObj, "type",
				 TournamentMatchParticipant::Type::Unknown);
	return (TournamentMatchParticipant::Type)obs_data_get_int(dataObj,
								  "type");
}

void TournamentMatchParticipant::load(obs_data_t *dataObj)
{
	// obs_log(LOG_INFO, "[TournamentMatchParticipant::load] called",
	// 	this->_type);
	this->_type = TournamentMatchParticipant::loadType(dataObj);
	obs_log(LOG_INFO, "[TournamentMatchParticipant::load] loaded type %d",
		this->_type);

	// this->_matchReference.load(referenceData);
}

void TournamentMatchParticipant::save(obs_data_t *dataObj) const
{
	obs_data_set_int(dataObj, "type", this->_type);
}

// TournamentMatchParticipant::ValidateResult::ValidateResult(
// 	TournamentMatchParticipant::ValidateResult::Type _type,
// 	TournamentMatchParticipant::ValidateResult::Data _data)
// 	: type(_type),
// 	  data(_data)
// {
// }
// // TournamentMatchParticipant::ValidateResult::ValidateResult() {}
//
// TournamentMatchParticipant::ValidateResult::~ValidateResult() {}

// TournamentMatchParticipant::ValidateResult::Data(InvalidData _data): invalid(_data) {}

// TournamentMatchParticipant::ValidateResult::ValidateResult(
// 	TournamentMatchParticipant::ValidateResult::InvalidData _data)
// 	: type(TournamentMatchParticipant::ValidateResult::Type::Invalid),
// 	  data(_data)
// {
// }
// TournamentMatchParticipant::ValidateResult::ValidateResult(
// 	TournamentMatchParticipant::ValidateResult::ValidData _data)
// 	: type(TournamentMatchParticipant::ValidateResult::Type::Valid),
// 	  data(_data)
// {
// }

// TournamentMatchParticipant::ValidateResult::~ValidateResult() {}

bool TournamentMatchParticipant::ValidateResult::isValid()
{
	return this->type ==
	       TournamentMatchParticipant::ValidateResult::Type::Valid;
}
