#pragma once

#include "src/model/match-reference.hpp"
#include "src/model/tournament-match-participant.hpp"

class TournamentMatch;

class TournamentMatchParticipantWinnerOfMatch
	: public TournamentMatchParticipant {
public:
	static TournamentMatchParticipantWinnerOfMatch *
	loadStatic(obs_data_t *dataObj);
	// loadStatic(obs_data_t *dataObj, MatchReference matchReference);
	// TournamentMatchParticipantWinnerOfMatch(TournamentMatch *match = nullptr);
	// TournamentMatchParticipantWinnerOfMatch(TournamentMatch *match = nullptr,
	// 					long long tournamentIndex = -1,
	// 					long long matchIndex = -1);
	// TournamentMatchParticipantWinnerOfMatch(obs_data_t *dataObj, long long tournamentIndex, long long winnerOfMatchIndex);
	TournamentMatchParticipantWinnerOfMatch(
		// MatchReference selfMatchReference,
		MatchReference winnerOfMatchReference = {});
	~TournamentMatchParticipantWinnerOfMatch();
	bool isValid() const override;
	bool isReady() const override;
	std::string displayName() const override;

	void save(obs_data_t *dataObj) const override;

private:
	// MatchReference _selfMatchReference;
	MatchReference _winnerOfMatchReference;
	// TournamentMatch *_match;
	// // std::string _displayName;
	//
	// long long _matchIndex;
	// long long _tournamentIndex;

	void load(obs_data_t *dataObj) override;
};
