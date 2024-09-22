#include "match-participant-from-match.hpp"
#include "src/data/data-helpers.hpp"
#include <obs-data.h>
#include <obs.hpp>
#include <stdexcept>

MatchParticipantFromMatch::MatchParticipantFromMatch() : MatchParticipant() {}

MatchParticipantFromMatch::~MatchParticipantFromMatch() {}

std::string MatchParticipantFromMatch::displayName() const
{
	throw std::runtime_error(
		"TODO MatchParticipantFromMatch::displayName()");
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

std::unique_ptr<MatchParticipantSelectionStrategy>
MatchParticipantSelectionStrategy::loadStatic(obs_data_t *data)
{
	auto selectionStrategyType =
		ObsDataHelpers::getEnum<MatchParticipantSelectionStrategy::Type>(
			data, "selectionStrategy",
			MatchParticipantSelectionStrategy::Type::Unknown);

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

MatchParticipant &SelectWinnerOfMatch::select(Match fromMatch)
{
	UNUSED_PARAMETER(fromMatch);
	throw std::runtime_error(
		"TODO SelectWinnerOfMatch::select(TournamentMatch)");
}

MatchParticipant &SelectLoserOfMatch::select(Match fromMatch)
{
	UNUSED_PARAMETER(fromMatch);
	throw std::runtime_error(
		"TODO SelectLoserOfMatch::select(TournamentMatch)");
}
