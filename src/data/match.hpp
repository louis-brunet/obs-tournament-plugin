#pragma once

#include "src/data/match-participant.hpp"
#include <memory>
#include <obs-data.h>
class Match {
public:
    Match();
    Match(Match &&) = default;
    Match(const Match &) = default;
    Match &operator=(Match &&) = default;
    Match &operator=(const Match &) = default;
    ~Match();

    // MatchParticipant &participant1();
    // MatchParticipant &participant2();

    void load(obs_data_t *data);
    void save(obs_data_t *data) const;

private:
    // MatchParticipant _participant1;
    // MatchParticipant _participant2;
    std::shared_ptr<MatchParticipant> _participant1;
    std::shared_ptr<MatchParticipant> _participant2;
};
