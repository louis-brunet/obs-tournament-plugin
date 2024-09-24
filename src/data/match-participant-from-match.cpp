#include "match-participant-from-match.hpp"
#include "src/data/match-reference-remap.hpp"
#include "src/data/data-helpers.hpp"
#include <obs-data.h>
#include <obs.hpp>
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
    throw std::runtime_error("TODO MatchParticipantFromMatch::displayName()");
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

void MatchParticipantFromMatch::applyRemap(const MatchReferenceRemap *remap)
{
    this->_fromMatchReference = remap->apply(this->_fromMatchReference);
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
