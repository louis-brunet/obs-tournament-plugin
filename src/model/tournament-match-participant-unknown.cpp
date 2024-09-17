#include "tournament-match-participant-unknown.hpp"

TournamentMatchParticipantUnknown::TournamentMatchParticipantUnknown()
	: TournamentMatchParticipant(TournamentMatchParticipant::Type::Unknown)
{
}

TournamentMatchParticipantUnknown::~TournamentMatchParticipantUnknown() {}

bool TournamentMatchParticipantUnknown::isValid() const
{
	return false;
}

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
