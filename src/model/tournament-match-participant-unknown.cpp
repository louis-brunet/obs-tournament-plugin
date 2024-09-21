#include "tournament-match-participant-unknown.hpp"
#include <obs-module.h>

TournamentMatchParticipantUnknown::TournamentMatchParticipantUnknown()
	: TournamentMatchParticipant(TournamentMatchParticipant::Type::Unknown)
{
}

TournamentMatchParticipantUnknown::~TournamentMatchParticipantUnknown() {}

TournamentMatchParticipant::ValidateResult
TournamentMatchParticipantUnknown::validate() const
{
	TournamentMatchParticipant::ValidateResult::InvalidData data{
		.message = obs_module_text(
			"Error.TournamentMatchParticipantUnknown.UnknownParticipant")};
	return TournamentMatchParticipant::ValidateResult(data);
}

// bool TournamentMatchParticipantUnknown::isValid() const
// {
// 	return false;
// }

bool TournamentMatchParticipantUnknown::isReady() const
{
	return false;
}

std::string TournamentMatchParticipantUnknown::displayName() const
{
	return "";
}

void TournamentMatchParticipantUnknown::save(obs_data_t *dataObj) const
{
	TournamentMatchParticipant::save(dataObj);
}

void TournamentMatchParticipantUnknown::load(obs_data_t *dataObj)
{
	TournamentMatchParticipant::load(dataObj);
}
