#pragma once

#include "src/data/match-reference.hpp"

class MatchReferenceRemap {
public:
    MatchReferenceRemap() = default;
    MatchReferenceRemap(const MatchReferenceRemap &) = default;
    MatchReferenceRemap(MatchReferenceRemap &&) = default;
    // MatchReferenceRemap &operator=(const MatchReferenceRemap &) = default;
    // MatchReferenceRemap &operator=(MatchReferenceRemap &&) = default;
    virtual ~MatchReferenceRemap() = default;

    virtual MatchReference apply(const MatchReference &oldReference) const = 0;
};

class MatchReferenceRemapAddedMatch : public MatchReferenceRemap {
public:
    MatchReferenceRemapAddedMatch(MatchReference addedMatch);
    ~MatchReferenceRemapAddedMatch() = default;

    MatchReference apply(const MatchReference &oldReference) const override;

private:
    MatchReference _addedMatch;
};

class MatchReferenceRemapDeletedMatch : public MatchReferenceRemap {
public:
    MatchReferenceRemapDeletedMatch(MatchReference deletedMatch);
    ~MatchReferenceRemapDeletedMatch() = default;

    MatchReference apply(const MatchReference &oldReference) const override;

private:
    MatchReference _deletedMatch;
};

class MatchReferenceRemapNone : public MatchReferenceRemap {
public:
    MatchReference apply(const MatchReference &oldReference) const override;
};

class MatchReferenceRemapSwappedMatch : public MatchReferenceRemap {
public:
    MatchReferenceRemapSwappedMatch(MatchReference from, MatchReference to);
    MatchReference apply(const MatchReference &oldReference) const override;

private:
    MatchReference _from;
    MatchReference _to;
};
