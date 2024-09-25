#include "match-participant-from-match.hpp"
#include "src/data/match-reference-remap.hpp"
#include "src/data/data-helpers.hpp"
#include "src/logger.hpp"
#include <obs-data.h>
#include <obs-module.h>
#include <obs.hpp>
#include <set>
#include <stdexcept>

MatchParticipantFromMatch::MatchParticipantFromMatch(
    MatchReference __fromMatchReference,
    std::unique_ptr<MatchParticipantSelectionStrategy> __selectionStrategy)
    : MatchParticipant(MatchParticipant::Type::FromMatch),
      _fromMatchReference(__fromMatchReference),
      _selectionStrategy(std::move(__selectionStrategy))
{
}

MatchParticipantFromMatch::MatchParticipantFromMatch(
    const MatchParticipantFromMatch &other)
    : MatchParticipant(other)
{
    this->_fromMatchReference = other._fromMatchReference;
    this->_selectionStrategy = MatchParticipantSelectionStrategy::loadStatic(
        other._selectionStrategy->type);
}

MatchParticipantFromMatch::~MatchParticipantFromMatch() {}

std::string MatchParticipantFromMatch::displayName() const
{
    return this->_selectionStrategy->displayName(
        this->fromMatchReference().toMatchLabel().c_str());
}

MatchParticipantSelectionStrategy::Type
MatchParticipantFromMatch::selectionStrategy() const
{
    return this->_selectionStrategy->type;
}

MatchReference MatchParticipantFromMatch::fromMatchReference() const
{
    return this->_fromMatchReference;
}

void MatchParticipantFromMatch::applyRemap(const MatchReferenceRemap *remap,
                                           const MatchReference &context)
{
    this->_fromMatchReference =
        remap->apply(this->_fromMatchReference, context);
}

void MatchParticipantFromMatch::load(obs_data_t *data)
{
    MatchParticipant::load(data);

    OBSDataAutoRelease fromMatchReferenceData =
        obs_data_get_obj(data, "fromMatchReference");
    if (fromMatchReferenceData) {
        this->_fromMatchReference.load(fromMatchReferenceData);
    }

    this->_selectionStrategy =
        MatchParticipantSelectionStrategy::loadStatic(data);
}

void MatchParticipantFromMatch::save(obs_data_t *data) const
{
    MatchParticipant::save(data);

    OBSDataAutoRelease fromMatchReferenceData = obs_data_create();
    this->_fromMatchReference.save(fromMatchReferenceData);
    obs_data_set_obj(data, "fromMatchReference", fromMatchReferenceData);

    obs_data_set_int(data, "selectionStrategy", this->_selectionStrategy->type);
}

std::shared_ptr<MatchParticipant> MatchParticipantFromMatch::duplicate() const
{
    return std::make_shared<MatchParticipantFromMatch>(*this);
}

MatchParticipant::ValidateConfigurationResult
MatchParticipantFromMatch::validateCircularDependencies(
    std::set<MatchReference> &seenMatchReferences,
    const MatchReference &recursiveMatchContext)
{
    if (!seenMatchReferences.insert(recursiveMatchContext).second) {
        return MatchParticipant::ValidateConfigurationResult::
            InvalidCircularDependency;
    }

    auto recMatch = recursiveMatchContext.match();
    for (auto p : {recMatch->participant1(), recMatch->participant2()}) {
        switch (p->type()) {
        case MatchParticipant::Unknown:
            break;
        case MatchParticipant::Player:
            break;
        case MatchParticipant::FromMatch:
            return MatchParticipantFromMatch::validateCircularDependencies(
                seenMatchReferences,
                std::reinterpret_pointer_cast<MatchParticipantFromMatch>(p)
                    ->_fromMatchReference);
            break;
        }
    }

    return ValidateConfigurationResult::Valid;
}

MatchParticipant::ValidateConfigurationResult
MatchParticipantFromMatch::validateConfiguration(
    const MatchReference &matchContextReference) const
{
    auto fromMatch = this->_fromMatchReference.match();
    if (!fromMatch) {
        throw std::runtime_error(
            "[MatchParticipantFromMatch::validateConfiguration] invalid fromMatch reference");
    }
    auto matchContext = matchContextReference.match();
    if (!matchContext) {
        throw std::runtime_error(
            "[MatchParticipantFromMatch::validateConfiguration] invalid match reference");
    }

    // auto cb = [&seenMatchReferences](MatchReference recursiveMatchContext) {
    //     if (!seenMatchReferences.insert(recursiveMatchContext).second) {
    //         return MatchParticipant::ValidateConfigurationResult::
    //             InvalidCircularDependency;
    //     }
    //
    //     auto recMatch = recursiveMatchContext.match();
    //     for (auto p : {recMatch->participant1(), recMatch->participant2()}) {
    //         switch (p->type()) {
    //         case MatchParticipant::Unknown:
    //             break;
    //         case MatchParticipant::Player:
    //             break;
    //         case MatchParticipant::FromMatch:
    //             return cb(
    //                 std::reinterpret_pointer_cast<MatchParticipantFromMatch>(p)
    //                     ->_fromMatchReference);
    //             break;
    //         }
    //     }
    // };
    //
    // auto tempMatchContextReference = this->_fromMatchReference;
    // while () {
    //     if (!seenMatchReferences.insert(tempMatchContextReference).second) {
    //         return MatchParticipant::ValidateConfigurationResult::
    //             InvalidCircularDependency;
    //     }
    // }

    std::shared_ptr<MatchParticipant> otherParticipant;
    if (matchContext->participant1().get() == this) {
        otherParticipant = matchContext->participant2();
    } else if (matchContext->participant2().get() == this) {
        otherParticipant = matchContext->participant1();
    } else {
        throw std::runtime_error(
            "[MatchParticipantFromMatch::validateConfiguration] given match reference does not contain this participant");
    }

    // std::set<MatchReference> seenMatchReferences = {matchContextReference};

    switch (otherParticipant->type()) {
    case MatchParticipant::Unknown:
        break;
    case MatchParticipant::Player:
        break;
    case MatchParticipant::FromMatch: {
        auto otherParticipantFromMatch =
            std::reinterpret_pointer_cast<MatchParticipantFromMatch>(
                otherParticipant);
        // TODO: could possibly be part of base case of recursive check
        if (*this == *otherParticipantFromMatch.get()) {
            return MatchParticipant::ValidateConfigurationResult::
                InvalidPlayerVersusSelf;
        }
            // Logger::log("[MatchParticipantFromMatch::validateConfiguration] other is from match but not equal");

        std::set<MatchReference> seenMatchReferences = {matchContextReference};
        auto circularDepsResult =
            MatchParticipantFromMatch::validateCircularDependencies(
                seenMatchReferences,
                otherParticipantFromMatch->_fromMatchReference);
        if (circularDepsResult != ValidateConfigurationResult::Valid) {
            return circularDepsResult;
        }

        break;
    }
    }

    std::set<MatchReference> seenMatchReferences = {matchContextReference};
    auto circularDepsResult =
        MatchParticipantFromMatch::validateCircularDependencies(
            seenMatchReferences, this->_fromMatchReference);
    if (circularDepsResult != ValidateConfigurationResult::Valid) {
        return circularDepsResult;
    }

    Logger::log(
        "[MatchParticipantFromMatch::validateConfiguration] Valid ref to match %s!",
        this->_fromMatchReference.toMatchLabel().c_str());
    // TODO: ?
    return ValidateConfigurationResult::Valid;
}

MatchParticipantSelectionStrategy::MatchParticipantSelectionStrategy(Type __type)
    : type(__type)
{
}

MatchParticipantSelectionStrategy::~MatchParticipantSelectionStrategy() {}

std::unique_ptr<MatchParticipantSelectionStrategy>
MatchParticipantSelectionStrategy::loadStatic(obs_data_t *data)
{
    auto selectionStrategyType =
        ObsDataHelpers::getEnum<MatchParticipantSelectionStrategy::Type>(
            data, "selectionStrategy",
            MatchParticipantSelectionStrategy::Type::Unknown);

    return MatchParticipantSelectionStrategy::loadStatic(selectionStrategyType);
}

std::unique_ptr<MatchParticipantSelectionStrategy>
MatchParticipantSelectionStrategy::loadStatic(
    MatchParticipantSelectionStrategy::Type selectionStrategyType)
{
    switch (selectionStrategyType) {
    case MatchParticipantSelectionStrategy::Loser:
        return std::make_unique<SelectLoserOfMatch>();

    case MatchParticipantSelectionStrategy::Winner:
        return std::make_unique<SelectWinnerOfMatch>();

    case MatchParticipantSelectionStrategy::Unknown:
    default:
        // return std::make_unique<SelectUnknown>();
        return nullptr;
    }
}

SelectWinnerOfMatch::SelectWinnerOfMatch()
    : MatchParticipantSelectionStrategy(
          MatchParticipantSelectionStrategy::Type::Winner)
{
}

MatchParticipant &SelectWinnerOfMatch::select(Match fromMatch)
{
    UNUSED_PARAMETER(fromMatch);
    throw std::runtime_error(
        "TODO SelectWinnerOfMatch::select(TournamentMatch)");
}

std::string SelectWinnerOfMatch::displayName(const char *matchLabel)
{
    return (std::string)obs_module_text("matchParticipant.winnerOfPrefix") +
           " " + matchLabel;
}

SelectLoserOfMatch::SelectLoserOfMatch()
    : MatchParticipantSelectionStrategy(
          MatchParticipantSelectionStrategy::Type::Loser)
{
}

MatchParticipant &SelectLoserOfMatch::select(Match fromMatch)
{
    UNUSED_PARAMETER(fromMatch);
    throw std::runtime_error(
        "TODO SelectLoserOfMatch::select(TournamentMatch)");
}

std::string SelectLoserOfMatch::displayName(const char *matchLabel)
{
    return (std::string)obs_module_text("matchParticipant.loserOfPrefix") +
           " " + matchLabel;
}
