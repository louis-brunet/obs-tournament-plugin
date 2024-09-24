#pragma once

#include "src/data/match-reference.hpp"
#include "src/data/tournament-round-reference.hpp"

class MatchReferenceRemap {
public:
    MatchReferenceRemap() = default;
    MatchReferenceRemap(const MatchReferenceRemap &) = default;
    MatchReferenceRemap(MatchReferenceRemap &&) = default;
    // MatchReferenceRemap &operator=(const MatchReferenceRemap &) = default;
    // MatchReferenceRemap &operator=(MatchReferenceRemap &&) = default;
    virtual ~MatchReferenceRemap() = default;

    virtual MatchReference apply(const MatchReference &oldReference, const MatchReference &context) const = 0;
};

class MatchReferenceRemapAddedMatch : public MatchReferenceRemap {
public:
    MatchReferenceRemapAddedMatch(MatchReference addedMatch);
    ~MatchReferenceRemapAddedMatch() = default;

    MatchReference apply(const MatchReference &oldReference, const MatchReference &context) const override;

private:
    MatchReference _addedMatch;
};

class MatchReferenceRemapDeletedMatch : public MatchReferenceRemap {
public:
    MatchReferenceRemapDeletedMatch(MatchReference deletedMatch);
    ~MatchReferenceRemapDeletedMatch() = default;

    MatchReference apply(const MatchReference &oldReference, const MatchReference &context) const override;

private:
    MatchReference _deletedMatch;
};

class MatchReferenceRemapNone : public MatchReferenceRemap {
public:
    MatchReference apply(const MatchReference &oldReference, const MatchReference &context) const override;
};

class MatchReferenceRemapSwappedMatch : public MatchReferenceRemap {
public:
    MatchReferenceRemapSwappedMatch(MatchReference from, MatchReference to);
    MatchReference apply(const MatchReference &oldReference, const MatchReference &context) const override;

private:
    MatchReference _from;
    MatchReference _to;
};

class MatchReferenceRemapDuplicatedRound : public MatchReferenceRemap {
public:
    MatchReferenceRemapDuplicatedRound(TournamentRoundReference addedRound);
    ~MatchReferenceRemapDuplicatedRound() = default;

    MatchReference apply(const MatchReference &oldReference, const MatchReference &context) const override;

private:
    TournamentRoundReference _addedRound;
};

class MatchReferenceRemapDeletedRound : public MatchReferenceRemap {
public:
    MatchReferenceRemapDeletedRound(TournamentRoundReference deletedRound);
    ~MatchReferenceRemapDeletedRound() = default;

    MatchReference apply(const MatchReference &oldReference, const MatchReference &context) const override;

private:
    TournamentRoundReference _deletedRound;
};
