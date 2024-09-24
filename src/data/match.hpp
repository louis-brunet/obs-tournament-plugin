#pragma once

#include "src/data/match-participant-unknown.hpp"
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

    std::shared_ptr<MatchParticipant> participant1();
    std::shared_ptr<MatchParticipant> participant2();
    void setParticipant1(std::shared_ptr<MatchParticipant> participant);
    void setParticipant2(std::shared_ptr<MatchParticipant> participant);

    std::shared_ptr<Match> duplicate() const;

    void load(obs_data_t *data);
    void save(obs_data_t *data) const;

private:
    // MatchParticipant _participant1;
    // MatchParticipant _participant2;
    std::shared_ptr<MatchParticipant> _participant1 = std::make_shared<MatchParticipantUnknown>();
    std::shared_ptr<MatchParticipant> _participant2 = std::make_shared<MatchParticipantUnknown>();
};
