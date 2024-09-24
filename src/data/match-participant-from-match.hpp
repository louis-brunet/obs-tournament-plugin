#pragma once

#include "src/data/match-participant.hpp"
#include "src/data/match-reference.hpp"
#include "src/data/match.hpp"
#include <memory>

class MatchParticipantSelectionStrategy {
public:
    enum Type {
        Unknown = -1,
        Loser = 0,
        Winner,
    };

    static std::unique_ptr<MatchParticipantSelectionStrategy>
    loadStatic(obs_data_t *data);
    static std::unique_ptr<MatchParticipantSelectionStrategy>
    loadStatic(MatchParticipantSelectionStrategy::Type selectionStrategyType);

    Type type;

    MatchParticipantSelectionStrategy(Type = Type::Unknown);
    MatchParticipantSelectionStrategy(MatchParticipantSelectionStrategy &&) =
        default;
    MatchParticipantSelectionStrategy(
        const MatchParticipantSelectionStrategy &) = default;
    MatchParticipantSelectionStrategy &
    operator=(MatchParticipantSelectionStrategy &&) = default;
    MatchParticipantSelectionStrategy &
    operator=(const MatchParticipantSelectionStrategy &) = default;
    ~MatchParticipantSelectionStrategy();

    virtual MatchParticipant &select(Match fromMatch) = 0;

private:
};

class SelectWinnerOfMatch : public MatchParticipantSelectionStrategy {
public:
    SelectWinnerOfMatch();
    ~SelectWinnerOfMatch();

    MatchParticipant &select(Match fromMatch);
};

class SelectLoserOfMatch : public MatchParticipantSelectionStrategy {
public:
    SelectLoserOfMatch();
    ~SelectLoserOfMatch();

    MatchParticipant &select(Match fromMatch);
};

class MatchParticipantFromMatch : public MatchParticipant {
public:
    MatchParticipantFromMatch(
        MatchReference fromMatchReference = MatchReference(),
        std::unique_ptr<MatchParticipantSelectionStrategy> selectionStrategy =
            std::make_unique<SelectWinnerOfMatch>());
    MatchParticipantFromMatch(MatchParticipantFromMatch &&) = default;
    MatchParticipantFromMatch(const MatchParticipantFromMatch &);
    MatchParticipantFromMatch &operator=(MatchParticipantFromMatch &&) = default;
    // MatchParticipantFromMatch &operator=(const MatchParticipantFromMatch &) = default;
    ~MatchParticipantFromMatch();

    std::string displayName() const override;
    MatchReference fromMatchReference() const;
    MatchParticipantSelectionStrategy::Type selectionStrategy() const;

    void load(obs_data_t *data) override;
    void save(obs_data_t *data) const override;
    void applyRemap(const MatchReferenceRemap *remap, const MatchReference &context) override;
    std::shared_ptr<MatchParticipant> duplicate() const override;

private:
    MatchReference _fromMatchReference;
    std::unique_ptr<MatchParticipantSelectionStrategy> _selectionStrategy;
};

// MatchParticipantFromMatch::MatchParticipantFromMatch() {
// }
//
// MatchParticipantFromMatch::~MatchParticipantFromMatch() {
// }
