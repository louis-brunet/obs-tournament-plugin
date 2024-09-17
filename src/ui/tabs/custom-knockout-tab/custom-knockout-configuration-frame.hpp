#pragma once

#include "src/model/custom-knockout-tournament.hpp"
#include "src/model/tournament-match.hpp"
#include <QBoxLayout>
#include <QFrame>
#include <cwchar>

class CustomKnockoutMatchConfigurationFrame : public QFrame {
public:
	CustomKnockoutMatchConfigurationFrame(CustomKnockoutTournament *tournament);
	~CustomKnockoutMatchConfigurationFrame();
	std::vector<TournamentMatch *> getTournamentMatches();

private:
    CustomKnockoutTournament *_tournament;
	// uint32_t totalMatchCount;
	// std::vector<Player *> players;
	QBoxLayout *matchListLayout;

	// void addMatch(std::string matchLabel, TournamentMatchParticipant *participant1 = nullptr, TournamentMatchParticipant *participant2 = nullptr);
	void addMatch(TournamentMatch *tournamentMatch = nullptr);
	void removeMatch();
	void updateAllPlayerOptions();
	std::string getMatchIdFromMatchIndex(uint32_t matchIndex);
};
