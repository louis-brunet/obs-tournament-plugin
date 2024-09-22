#include "tournament-match-participant-winner-of-match.hpp"
#include "src/model/tournament-match.hpp"
#include <functional>
#include <obs-data.h>
#include <obs-module.h>
#include <obs.hpp>
#include <set>
#include <stdexcept>

TournamentMatchParticipantWinnerOfMatch::TournamentMatchParticipantWinnerOfMatch(
	// MatchReference selfMatchReference,
	MatchReference winnerOfMatchReference)
	: TournamentMatchParticipant(
		  TournamentMatchParticipant::Type::WinnerOfMatch),
	  // TournamentMatchParticipant::Type::WinnerOfMatch, selfMatchReference),
	  // _selfMatchReference(selfMatchReference),
	  _winnerOfMatchReference(winnerOfMatchReference)
{
}

// TournamentMatchParticipantWinnerOfMatch::TournamentMatchParticipantWinnerOfMatch(
// 	TournamentMatch *match, long long tournamentIndex, long long matchIndex)
// 	: TournamentMatchParticipant(
// 		  TournamentMatchParticipant::Type::WinnerOfMatch),
// 	  _match(match),
// 	  _matchIndex(matchIndex),
// 	  _tournamentIndex(tournamentIndex)
// {
// }

TournamentMatchParticipantWinnerOfMatch::
	~TournamentMatchParticipantWinnerOfMatch()
{
}

TournamentMatchParticipant::ValidateResult
TournamentMatchParticipantWinnerOfMatch::validate(
	MatchReference &matchReference) const
{
	auto match = this->_winnerOfMatchReference.match();

	if (!match) {
		TournamentMatchParticipant::ValidateResult::InvalidData data{
			.message = obs_module_text(
				"Error.TournamentMatchParticipantWinnerOfMatch.InvalidMatchReference")};
		return TournamentMatchParticipant::ValidateResult(data);
	}

	// std::set<MatchReference *> s;
	// std::function<void(std::set<MatchReference *> & s)> cb =
	// 	[&cb](std::set<MatchReference *> &s, ) {
	// 		MatchReference *mr = nullptr;
	// 		// auto h = s.insert(mr);
	// 		auto a = s.insert(mr);
	// 		auto isInserted = a.second;
	// 		if (!isInserted) {
	// 			// already seen
	// 			return true;
	// 		}
	// 		return cb(s);
	// 	};
	// // if (s.find(mr) != s.end()) {
	// // }
	//
	// if (this->hasCircularDependency(matchReference)) {
	// 	TournamentMatchParticipant::ValidateResult::InvalidData data{
	// 		.message = obs_module_text(
	// 			"Error.TournamentMatchParticipantWinnerOfMatch.CircularDependency")};
	// 	return TournamentMatchParticipant::ValidateResult(data);
	// }
	// TODO: check for circular dependency?
    UNUSED_PARAMETER(matchReference);

	TournamentMatchParticipant::ValidateResult::ValidData data{};
	return TournamentMatchParticipant::ValidateResult(data);
}

// bool TournamentMatchParticipantWinnerOfMatch::isValid() const
// {
//     return true; // TODO: isValid
// 	// TODO: check for circular dependency?
// 	// return this->_match != nullptr;
// }

bool TournamentMatchParticipantWinnerOfMatch::isReady() const
{
	if (!this->validate()->isValid()) {
		return false;
	}

	// TODO: how to tell if "winner of match" is ready? hasWinner method in TournamentMatch?
	throw std::runtime_error("TODO winner of match isReady");
	return false;
}

std::string TournamentMatchParticipantWinnerOfMatch::displayName() const
{
	std::string matchLabel;
	auto match = this->_winnerOfMatchReference.match();
	if (match) {
		matchLabel = match->matchLabel();
	} else {
		matchLabel = "???";
	}
	return obs_module_text("WinnerOfMatch") + (std::string) " " +
	       matchLabel;
}

void TournamentMatchParticipantWinnerOfMatch::save(obs_data_t *dataObj) const
{
	TournamentMatchParticipant::save(dataObj);
	OBSDataAutoRelease winnerOfMatchReferenceData = obs_data_create();
	this->_winnerOfMatchReference.save(winnerOfMatchReferenceData);
	obs_data_set_obj(dataObj, "winnerOfMatchReference",
			 winnerOfMatchReferenceData);

	//    auto winnerOfMatch = this->_winnerOfMatchReference.match();
	// if (winnerOfMatch) {
	//        OBSDataAutoRelease referenceDataObj = obs_data_create();
	//        this
	// 	// obs_data_set_int(dataObj, "winnerOfMatchIndex",
	// 	// 		 this->_w);
	// 	// OBSDataAutoRelease matchData = obs_data_create();
	// 	// this->_match->save(matchData);
	// 	// obs_data_set_obj(dataObj, "match", matchData);
	// }
}

void TournamentMatchParticipantWinnerOfMatch::load(obs_data_t *dataObj)
{
	TournamentMatchParticipant::load(dataObj);

	OBSDataAutoRelease winnerOfMatchReferenceData =
		obs_data_get_obj(dataObj, "winnerOfMatchReference");
	this->_winnerOfMatchReference.load(winnerOfMatchReferenceData);
	// if (!dataObj) {
	// 	return;
	// }

	// this->_matchIndex = obs_data_get_int(dataObj, "winnerOfMatchIndex");
	//
	// // FIXME: _match is only set in loadStatic, it should also be set here ideally
	// this->_match = nullptr;
	// obs_log(LOG_INFO,
	// 	"[TournamentMatchParticipantWinnerOfMatch::load] loading tournamentMatch");
	// OBSDataAutoRelease matchData = obs_data_get_obj(dataObj, "match");
	// this->_match = TournamentMatch::loadStatic(matchData);
}

TournamentMatchParticipantWinnerOfMatch *
TournamentMatchParticipantWinnerOfMatch::loadStatic(obs_data_t *dataObj)
{
	auto participant = new TournamentMatchParticipantWinnerOfMatch();
	participant->load(dataObj);
	// participant->_match =
	// 	tournament.matches.at((unsigned long)participant->_matchIndex);
	return participant;
}
