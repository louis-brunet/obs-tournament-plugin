#pragma once

#include <obs-data.h>
class Tournament;

class TournamentReference {
public:
	TournamentReference(long long tournamentIndex = -1);
	TournamentReference(TournamentReference &&) = default;
	TournamentReference(const TournamentReference &) = default;
	TournamentReference &operator=(TournamentReference &&) = default;
	TournamentReference &operator=(const TournamentReference &) = default;
	~TournamentReference();

    void load(obs_data_t *data);

    long long tournamentIndex = -1;

	Tournament *tournament();

// private:
};
