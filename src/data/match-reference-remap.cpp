#include "match-reference-remap.hpp"

MatchReferenceRemapAddedMatch::MatchReferenceRemapAddedMatch(
    MatchReference addedMatch)
    : _addedMatch(addedMatch)
{
}

MatchReference
MatchReferenceRemapAddedMatch::apply(const MatchReference &oldReference,
                                     const MatchReference &context) const
{
    UNUSED_PARAMETER(context);
    // MatchReference newReference(oldReference);
    // newReference.matchIndex++;

    auto addedTournamentIndex =
        this->_addedMatch.roundReference.tournamentReference.tournamentIndex;
    auto oldTournamentIndex =
        oldReference.roundReference.tournamentReference.tournamentIndex;
    if (oldTournamentIndex != addedTournamentIndex) {
        return oldReference;
    }

    auto addedRoundIndex = this->_addedMatch.roundReference.roundIndex;
    auto oldRoundIndex = oldReference.roundReference.roundIndex;
    if (oldRoundIndex != addedRoundIndex) {
        return oldReference;
    }

    auto addedMatchIndex = this->_addedMatch.matchIndex;
    auto oldMatchIndex = oldReference.matchIndex;
    if (oldMatchIndex < addedMatchIndex) {
        return oldReference;
    }

    MatchReference newReference(oldReference);
    newReference.matchIndex++;
    return newReference;
}

MatchReferenceRemapDeletedMatch::MatchReferenceRemapDeletedMatch(
    MatchReference deletedMatch)
    : _deletedMatch(deletedMatch)
{
}

MatchReference
MatchReferenceRemapDeletedMatch::apply(const MatchReference &oldReference,
                                       const MatchReference &context) const
{
    UNUSED_PARAMETER(context);

    MatchReference newReference(oldReference);
    newReference.matchIndex--;

    auto deletedTournamentIndex =
        this->_deletedMatch.roundReference.tournamentReference.tournamentIndex;
    auto oldTournamentIndex =
        oldReference.roundReference.tournamentReference.tournamentIndex;
    if (oldTournamentIndex != deletedTournamentIndex) {
        return oldReference;
    }

    auto deletedRoundIndex = this->_deletedMatch.roundReference.roundIndex;
    auto oldRoundIndex = oldReference.roundReference.roundIndex;
    if (oldRoundIndex != deletedRoundIndex) {
        return oldReference;
    }

    auto deletedMatchIndex = this->_deletedMatch.matchIndex;
    auto oldMatchIndex = oldReference.matchIndex;
    if (oldMatchIndex < deletedMatchIndex) {
        return oldReference;
    }
    if (oldMatchIndex == deletedMatchIndex) {
        newReference.matchIndex = -1;
        return newReference;
    }

    // NOTE: reference become invalid (-1) if deleted index 0 and oldRef.matchIndex = deleted.matchINdex
    return newReference;
}

MatchReference
MatchReferenceRemapNone::apply(const MatchReference &oldReference,
                               const MatchReference &context) const
{
    UNUSED_PARAMETER(context);

    return oldReference;
}

MatchReferenceRemapSwappedMatch::MatchReferenceRemapSwappedMatch(
    MatchReference __from, MatchReference __to)
    : _from(__from),
      _to(__to)
{
}

MatchReference
MatchReferenceRemapSwappedMatch::apply(const MatchReference &oldReference,
                                       const MatchReference &context) const
{
    UNUSED_PARAMETER(context);
    if (oldReference == this->_from) {
        return this->_to;
    }
    if (oldReference == this->_to) {
        return this->_from;
    }
    return oldReference;
}

MatchReferenceRemapDuplicatedRound::MatchReferenceRemapDuplicatedRound(
    TournamentRoundReference addedRound)
    : _addedRound(addedRound)
{
}

MatchReference
MatchReferenceRemapDuplicatedRound::apply(const MatchReference &oldReference,
                                          const MatchReference &context) const
{
    auto addedTournamentIndex =
        this->_addedRound.tournamentReference.tournamentIndex;
    auto oldTournamentIndex =
        oldReference.roundReference.tournamentReference.tournamentIndex;
    if (oldTournamentIndex != addedTournamentIndex) {
        return oldReference;
    }

    auto addedRoundIndex = this->_addedRound.roundIndex;
    auto oldRoundIndex = oldReference.roundReference.roundIndex;

    // NOTE: "- 1" to also remap references that were duplicated
    //  .... doesn't work, also remaps refs to round 1 from round X when round 1 is duplicated
    // if (oldRoundIndex < addedRoundIndex - 1) {

    TournamentRoundReference newRoundReference(
        oldReference.roundReference.tournamentReference,
        oldReference.roundReference.roundIndex + 1);

    auto isDuplicatedReference = oldRoundIndex == addedRoundIndex - 1;
    auto isRemappingContextNewRound = context.roundReference.roundIndex ==
                                      addedRoundIndex;
    auto isAfterDuplicatedRound = oldRoundIndex >= addedRoundIndex;
    if ((isDuplicatedReference && isRemappingContextNewRound) ||
        isAfterDuplicatedRound) {
        // remap duplicated references only when in newly duplicated round context
        return MatchReference(newRoundReference, oldReference.matchIndex);
    }

    return oldReference;
}
