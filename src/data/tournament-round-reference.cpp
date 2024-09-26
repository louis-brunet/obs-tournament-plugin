#include "tournament-round-reference.hpp"
#include "src/data/tournament-round.hpp"
#include "src/data/tournament.hpp"
#include <obs.hpp>

TournamentRoundReference::TournamentRoundReference(
    TournamentReference _tournamentReference, long long _roundIndex)
    : tournamentReference(_tournamentReference),
      roundIndex(_roundIndex)
{
}

TournamentRoundReference::~TournamentRoundReference() {}

void TournamentRoundReference::load(obs_data_t *data)
{
    OBSDataAutoRelease tournamentReferenceData =
        obs_data_get_obj(data, "tournamentReference");
    if (tournamentReferenceData) {
        this->tournamentReference.load(tournamentReferenceData);
    } else {
        this->tournamentReference = TournamentReference();
    }

    obs_data_set_default_int(data, "roundIndex", -1);
    this->roundIndex = obs_data_get_int(data, "roundIndex");
}

void TournamentRoundReference::save(obs_data_t *data) const
{
    OBSDataAutoRelease tournamentReferenceData = obs_data_create();
    this->tournamentReference.save(tournamentReferenceData);
    obs_data_set_obj(data, "tournamentReference", tournamentReferenceData);

    obs_data_set_int(data, "roundIndex", this->roundIndex);
}

std::shared_ptr<TournamentRound> TournamentRoundReference::round() const
{
    auto tournament = this->tournamentReference.tournament();
    if (this->roundIndex < 0 ||
        (unsigned long)this->roundIndex >= tournament->rounds().size()) {
        return nullptr;
    }

    return tournament->rounds().at((unsigned long)this->roundIndex);
}
