#pragma once

#include "src/data/match-participant.hpp"
#include "src/model/tournament-match.hpp"
#include <memory>

class MatchParticipantSelectionStrategy {
public:
	enum Type {
		Unknown = -1,
		Loser = 0,
		Winner,
	};

	static std::unique_ptr<MatchParticipantSelectionStrategy>
	loadStatic(obs_data_t *data);

	MatchParticipantSelectionStrategy();
	MatchParticipantSelectionStrategy(
		MatchParticipantSelectionStrategy &&) = default;
	MatchParticipantSelectionStrategy(
		const MatchParticipantSelectionStrategy &) = default;
	MatchParticipantSelectionStrategy &
	operator=(MatchParticipantSelectionStrategy &&) = default;
	MatchParticipantSelectionStrategy &
	operator=(const MatchParticipantSelectionStrategy &) = default;
	~MatchParticipantSelectionStrategy();

	virtual MatchParticipant &select(TournamentMatch fromMatch) = 0;

private:
};

class SelectWinnerOfMatch : public MatchParticipantSelectionStrategy {
	MatchParticipant &select(TournamentMatch fromMatch);
};

class SelectLoserOfMatch : public MatchParticipantSelectionStrategy {
	MatchParticipant &select(TournamentMatch fromMatch);
};

class MatchParticipantFromMatch : public MatchParticipant {
public:
	MatchParticipantFromMatch();
	MatchParticipantFromMatch(MatchParticipantFromMatch &&) = default;
	// MatchParticipantFromMatch(const MatchParticipantFromMatch &) = default;
	// MatchParticipantFromMatch &operator=(MatchParticipantFromMatch &&) = default;
	// MatchParticipantFromMatch &operator=(const MatchParticipantFromMatch &) = default;
	~MatchParticipantFromMatch();

	std::string displayName() const override;
	void load(obs_data_t *data) override;

private:
	MatchReference _fromMatchReference;
	std::unique_ptr<MatchParticipantSelectionStrategy> _selectionStrategy;
};

// MatchParticipantFromMatch::MatchParticipantFromMatch() {
// }
//
// MatchParticipantFromMatch::~MatchParticipantFromMatch() {
// }
