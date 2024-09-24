#include "match-reference.hpp"
#include "src/data/tournament.hpp"
#include "src/logger.hpp"
#include <obs.hpp>
#include <stdexcept>

MatchReference::MatchReference(
    TournamentRoundReference _tournamentRoundReference, long long _matchIndex)
    : roundReference(_tournamentRoundReference),
      matchIndex(_matchIndex)
{
}

MatchReference::~MatchReference() {}

void MatchReference::load(obs_data_t *data)
{
    OBSDataAutoRelease roundReferenceData = obs_data_get_obj(data, "roundReference");
    if (roundReferenceData) {
        this->roundReference.load(roundReferenceData);
    } else {
        this->roundReference = TournamentRoundReference();
    }

    obs_data_set_default_int(data, "matchIndex", -1);
    this->matchIndex = obs_data_get_int(data, "matchIndex");
}

void MatchReference::save(obs_data_t *data) const {
    OBSDataAutoRelease roundReferenceData = obs_data_create();
    this->roundReference.save(roundReferenceData);
    obs_data_set_obj(data, "roundReference", roundReferenceData);

    obs_data_set_int(data, "matchIndex", this->matchIndex);
}

std::string MatchReference::toMatchLabel() {
    Logger::log(LOG_DEBUG, "[MatchReference::toMatchLabel()] called");

    std::shared_ptr<Tournament> tournament =
        this->roundReference.tournamentReference.tournament();

    Logger::log(LOG_DEBUG, "[MatchReference::toMatchLabel()] tournament is %p", tournament.get());

    if (!tournament.get()) {
        return MatchReference::INVALID_MATCH_REFERENCE_LABEL;
        // return "[INVALID TOURNAMENT REF]";
    }

    auto rounds = tournament->rounds();
    auto roundIndex = this->roundReference.roundIndex;
    if (roundIndex < 0) {
        return MatchReference::INVALID_MATCH_REFERENCE_LABEL;
        // throw std::runtime_error(
        //     "[MatchReference::toMatchLabel()] roundIndex is negative");
    }
    if (!this->match()) {
        return MatchReference::INVALID_MATCH_REFERENCE_LABEL;
    }

    unsigned long totalMatchIndex = 0;
    for (unsigned long previousRoundIndex = 0;
         previousRoundIndex < (unsigned long)roundIndex; previousRoundIndex++) {
        totalMatchIndex += rounds.at(previousRoundIndex)->matches().size();
    }
    totalMatchIndex += (unsigned long)this->matchIndex;

    std::string matchLabel = "";
    long long tempMatchIndex = (long long)totalMatchIndex;

    // matchIdResult += (char) (((uint16_t) 'A') + (matchIndex % 26));
    // matchIndex = (matchIndex / 26) - 1;

    while (tempMatchIndex >= 0) {
        matchLabel =
            (char)(((int32_t)'A') + (tempMatchIndex % 26)) + matchLabel;
        tempMatchIndex = (tempMatchIndex / 26) - 1;
    };

    return matchLabel;
}

std::shared_ptr<Match> MatchReference::match() const
{
    auto tournamentRound = this->roundReference.round();
	if (this->matchIndex < 0 ||
	    (unsigned long)this->matchIndex >= tournamentRound->matches().size()
		    ) {
		return nullptr;
	}

	return tournamentRound->matches().at((unsigned long)this->matchIndex);
}
