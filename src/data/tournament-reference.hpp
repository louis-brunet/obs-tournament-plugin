#pragma once

class Tournament;

class TournamentReference {
public:
	TournamentReference(long long tournamentIndex = -1);
	TournamentReference(TournamentReference &&) = default;
	TournamentReference(const TournamentReference &) = default;
	TournamentReference &operator=(TournamentReference &&) = default;
	TournamentReference &operator=(const TournamentReference &) = default;
	~TournamentReference();

    long long tournamentIndex;

	Tournament *tournament();

// private:
};
