#include "match-participant-unknown.hpp"
#include <stdexcept>

MatchParticipantUnknown::MatchParticipantUnknown() : MatchParticipant() {}

MatchParticipantUnknown::~MatchParticipantUnknown() {}

std::string MatchParticipantUnknown::displayName() const
{
	throw std::runtime_error("TODO MatchParticipantUnknown::displayName()");
}

void MatchParticipantUnknown::load(obs_data_t *data)
{
	MatchParticipant::load(data);
}
