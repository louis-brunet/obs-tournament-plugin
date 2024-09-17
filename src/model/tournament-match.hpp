#pragma once

#include "src/model/match-reference.hpp"
#include "src/model/plugin-data-object.hpp"
#include "src/model/tournament-match-participant.hpp"
#include <memory>

// class TournamentMatchParticipant;

class TournamentMatch : public TournamentPluginDataObject {
public:
	static TournamentMatch *loadStatic(obs_data_t *dataObj, MatchReference reference);

    TournamentMatch(MatchReference reference);
	// TournamentMatch(Player *player1, Player *player2);
	// TournamentMatch(const char *matchLabel = "",
	// 		TournamentMatchParticipant *player1 = nullptr,
	// 		TournamentMatchParticipant *player2 = nullptr);
	~TournamentMatch();

    std::string matchLabel() const;
	TournamentMatchParticipant *participant1();
	TournamentMatchParticipant *participant2();
	void setParticipant1(TournamentMatchParticipant *);
	void setParticipant2(TournamentMatchParticipant *);

	void save(obs_data_t *dataObj) const;
	void load(obs_data_t *dataObj);

private:
    std::string _matchLabel;
	// std::array<std::unique_ptr<TournamentMatchParticipant>, 2> participants;
    std::unique_ptr<TournamentMatchParticipant> _participant1;
    std::unique_ptr<TournamentMatchParticipant> _participant2;

    MatchReference _reference;
};
