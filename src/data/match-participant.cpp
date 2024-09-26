#include "match-participant.hpp"
#include "src/data/data-helpers.hpp"
#include "src/data/match-participant-from-match.hpp"
#include "src/data/match-participant-unknown.hpp"
#include "src/data/match-participant-player.hpp"
#include "src/data/match-reference-remap.hpp"
#include <memory>
#include <util/c99defs.h>

static MatchParticipant::Type loadMatchParticipantType(obs_data_t *data)
{
    auto type = ObsDataHelpers::getInt(
        data, "type", MatchParticipant::Type::ParticipantUnknown);
    return static_cast<MatchParticipant::Type>(type);
}

std::shared_ptr<MatchParticipant> MatchParticipant::loadStatic(obs_data_t *data)
{
    auto type = loadMatchParticipantType(data);

    std::shared_ptr<MatchParticipant> participant;

    switch (type) {
    case ParticipantUnknown:
        participant = std::make_shared<MatchParticipantUnknown>();
        break;
    case ParticipantPlayer:
        participant = std::make_shared<MatchParticipantPlayer>();
        break;
    case ParticipantFromMatch:
        participant = std::make_shared<MatchParticipantFromMatch>();
        break;
    }
    participant->load(data);

    return participant;
}

MatchParticipant::MatchParticipant(MatchParticipant::Type __type)
    : _type(__type)
{
}

MatchParticipant::~MatchParticipant() {}

void MatchParticipant::load(obs_data_t *data)
{
    this->_type = ObsDataHelpers::getEnum<MatchParticipant::Type>(
        data, "type", MatchParticipant::Type::ParticipantUnknown);
}

void MatchParticipant::save(obs_data_t *data) const
{
    obs_data_set_int(data, "type", this->_type);
}

MatchParticipant::Type MatchParticipant::type() const
{
    return this->_type;
}

void MatchParticipant::applyRemap(const MatchReferenceRemap *remap,
                                  const MatchReference &context)
{
    UNUSED_PARAMETER(remap);
    UNUSED_PARAMETER(context);
}
