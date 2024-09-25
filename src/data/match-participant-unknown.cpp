#include "match-participant-unknown.hpp"

MatchParticipantUnknown::MatchParticipantUnknown()
    : MatchParticipant(MatchParticipant::Type::Unknown)
{
}

MatchParticipantUnknown::~MatchParticipantUnknown() {}

std::string MatchParticipantUnknown::displayName() const
{
    return "[???]";
}

void MatchParticipantUnknown::load(obs_data_t *data)
{
    MatchParticipant::load(data);
}

void MatchParticipantUnknown::save(obs_data_t *data) const
{
    MatchParticipant::save(data);
}

std::shared_ptr<MatchParticipant> MatchParticipantUnknown::duplicate() const
{
    auto newParticipant = std::make_shared<MatchParticipantUnknown>(*this);
    return newParticipant;
}

MatchParticipant::ValidateConfigurationResult
MatchParticipantUnknown::validateConfiguration(
    const MatchReference &matchContext) const
{
    UNUSED_PARAMETER(matchContext);
    return MatchParticipant::ValidateConfigurationResult::
        InvalidUnknownParticipant;
}
