#pragma once

#include "src/data/match.hpp"
#include "src/data/tournament-round-reference.hpp"
#include <obs-data.h>

class MatchReference {
public:
    static inline const std::string INVALID_MATCH_REFERENCE_LABEL =
        "[INVALID MATCH REFERENCE]";

    MatchReference(
        TournamentRoundReference roundReference = TournamentRoundReference(),
        long long matchIndex = -1);
    MatchReference(MatchReference &&) = default;
    MatchReference(const MatchReference &) = default;
    MatchReference &operator=(MatchReference &&) = default;
    MatchReference &operator=(const MatchReference &) = default;
    ~MatchReference();
    inline bool operator==(const MatchReference &rhs) const
    {
        return std::tie(this->roundReference, this->matchIndex) ==
               std::tie(rhs.roundReference, rhs.matchIndex);
    };
    inline bool operator!=(const MatchReference &rhs) const
    {
        return !(*this == rhs);
    };
    inline bool operator<(const MatchReference &rhs) const
    {
        return this->roundReference < rhs.roundReference ||
            (this->roundReference == rhs.roundReference &&
             this->matchIndex < rhs.matchIndex);
    };

    TournamentRoundReference roundReference = TournamentRoundReference();
    long long matchIndex = -1;

    std::string toMatchLabel() const;
    std::shared_ptr<Match> match() const;

    void load(obs_data_t *data);
    void save(obs_data_t *data) const;
};

// MatchReference::MatchReference() {
// }
//
// MatchReference::~MatchReference() {
// }
