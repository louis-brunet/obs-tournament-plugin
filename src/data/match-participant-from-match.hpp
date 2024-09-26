#pragma once

#include "src/data/match-participant.hpp"
#include "src/data/match-reference.hpp"
#include "src/data/match.hpp"
#include <memory>
#include <set>

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

    virtual std::shared_ptr<MatchParticipant>
    select(const MatchReference &fromMatch) = 0;
    virtual std::string displayName(const char *matchLabel) = 0;

private:
};

class SelectWinnerOfMatch : public MatchParticipantSelectionStrategy {
public:
    SelectWinnerOfMatch();
    ~SelectWinnerOfMatch();

    std::shared_ptr<MatchParticipant> select(const MatchReference &fromMatch);
    std::string displayName(const char *matchLabel);
};

class SelectLoserOfMatch : public MatchParticipantSelectionStrategy {
public:
    SelectLoserOfMatch();
    ~SelectLoserOfMatch();

    std::shared_ptr<MatchParticipant> select(const MatchReference &fromMatch);
    std::string displayName(const char *matchLabel);
};

class MatchParticipantFromMatch : public MatchParticipant {
public:
    MatchParticipantFromMatch(
        MatchReference fromMatchReference = MatchReference(),
        std::unique_ptr<MatchParticipantSelectionStrategy> selectionStrategy =
            std::make_unique<SelectWinnerOfMatch>());
    MatchParticipantFromMatch(MatchParticipantFromMatch &&) = default;
    MatchParticipantFromMatch(const MatchParticipantFromMatch &);
    MatchParticipantFromMatch &
    operator=(MatchParticipantFromMatch &&) = default;
    // MatchParticipantFromMatch &operator=(const MatchParticipantFromMatch &) = default;
    ~MatchParticipantFromMatch();
    inline bool operator==(const MatchParticipantFromMatch &rhs) const
    {
        return std::tie(this->_fromMatchReference,
                        this->_selectionStrategy->type) ==
               std::tie(rhs._fromMatchReference, rhs._selectionStrategy->type);
    };

    std::string displayName() const override;
    MatchReference fromMatchReference() const;
    MatchParticipantSelectionStrategy::Type selectionStrategy() const;

    void load(obs_data_t *data) override;
    void save(obs_data_t *data) const override;
    void applyRemap(const MatchReferenceRemap *remap,
                    const MatchReference &context) override;
    std::shared_ptr<MatchParticipant> duplicate() const override;
    ValidateConfigurationResult
    validateConfiguration(const MatchReference &matchContext) const override;
    std::shared_ptr<Player> determinedPlayer() const override;

private:
    static MatchParticipant::ValidateConfigurationResult
    validateCircularDependencies(std::set<MatchReference> &seenMatchReferences,
                                 const MatchReference &recursiveMatchContext);

    MatchReference _fromMatchReference;
    std::unique_ptr<MatchParticipantSelectionStrategy> _selectionStrategy;
};

// MatchParticipantFromMatch::MatchParticipantFromMatch() {
// }
//
// MatchParticipantFromMatch::~MatchParticipantFromMatch() {
// }
