#include "player-reference.hpp"
#include "src/data/tournament.hpp"
#include <obs.hpp>

PlayerReference::PlayerReference(TournamentReference __tournamentReference,
                                 long long __playerIndex)
    : tournamentReference(__tournamentReference),
      playerIndex(__playerIndex)
{
}

PlayerReference::~PlayerReference() {}

std::shared_ptr<Player> PlayerReference::player() const
{
    std::shared_ptr<Tournament> tournament =
        this->tournamentReference.tournament();

    if (!tournament) {
        return nullptr;
    }

    if (this->playerIndex < 0 ||
        (unsigned long)this->playerIndex >= tournament->players().size()) {
        return nullptr;
    }

    return tournament->players().at((unsigned long)this->playerIndex);
}

void PlayerReference::load(obs_data_t *data) {
    OBSDataAutoRelease tournamentData = obs_data_get_obj(data, "tournamentReference");
    this->tournamentReference.load(tournamentData);

    obs_data_set_default_int(data, "playerIndex", -1);
    this->playerIndex = obs_data_get_int(data, "playerIndex");
}

void PlayerReference::save(obs_data_t *data) const {

    OBSDataAutoRelease tournamentData = obs_data_create();
    this->tournamentReference.save(tournamentData);
    obs_data_set_obj(data, "tournamentReference", tournamentData);

    obs_data_set_int(data, "playerIndex", this->playerIndex);
}
