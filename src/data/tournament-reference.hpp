#pragma once

#include <memory>
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
    inline bool operator==(const TournamentReference &rhs) const
    {
        return this->tournamentIndex == rhs.tournamentIndex;
    };

    long long tournamentIndex = -1;

    std::shared_ptr<Tournament> tournament() const;

	void load(obs_data_t *data);
	void save(obs_data_t *data) const;
};
