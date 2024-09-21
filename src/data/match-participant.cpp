#include "match-participant.hpp"
#include "src/data/data-helpers.hpp"
#include "src/data/match-participant-from-match.hpp"
#include "src/data/match-participant-unknown.hpp"
#include "src/data/match-participant-player.hpp"
#include <memory>

static MatchParticipant::Type loadMatchParticipantType(obs_data_t *data)
{
	auto type = ObsDataHelpers::getInt(data, "type",
					   MatchParticipant::Type::Unknown);
	return static_cast<MatchParticipant::Type>(type);
}

std::shared_ptr<MatchParticipant> MatchParticipant::loadStatic(obs_data_t *data)
{
	auto type = loadMatchParticipantType(data);

	std::shared_ptr<MatchParticipant> participant;

	switch (type) {
	case Unknown:
		participant = std::make_shared<MatchParticipantUnknown>();
		break;
	case Player:
		participant = std::make_shared<MatchParticipantPlayer>();
		break;
	case FromMatch:
		participant = std::make_shared<MatchParticipantFromMatch>();
		break;
	}
	participant->load(data);

	return participant;
}

MatchParticipant::MatchParticipant() {}

MatchParticipant::~MatchParticipant() {}

void MatchParticipant::load(obs_data_t *data)
{
	this->_type = ObsDataHelpers::getEnum<MatchParticipant::Type>(
		data, "type", MatchParticipant::Type::Unknown);
}
