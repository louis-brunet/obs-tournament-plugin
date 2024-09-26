#include "tournament.hpp"
#include "src/data/data-helpers.hpp"
#include "src/logger.hpp"
#include <memory>
#include <obs.hpp>

Tournament::Tournament() {}

Tournament::~Tournament() {}

void Tournament::load(obs_data_t *data,
                      const TournamentReference &tournamentReference)
{
    UNUSED_PARAMETER(tournamentReference);

    this->_name = "";
    this->_players.clear();
    this->_rounds.clear();

    this->_name = ObsDataHelpers::getString(data, "name");
    this->_type = ObsDataHelpers::getEnum<Tournament::Type>(
        data, "type", Tournament::Type::Unknown);
    this->_isStarted = ObsDataHelpers::getBool(data, "isStarted", false);

    OBSDataAutoRelease outputsData = obs_data_get_obj(data, "outputs");
    this->outputs.load(outputsData);

    ObsDataHelpers::iterateArray(data, "players",
                                 [this](obs_data_t *itemDataObj,
                                        unsigned long playerIndex) {
                                     UNUSED_PARAMETER(playerIndex);

                                     auto player = std::make_shared<Player>();
                                     player->load(itemDataObj);

                                     this->_players.push_back(player);
                                 });

    ObsDataHelpers::iterateArray(
        data, "rounds",
        [this](obs_data_t *itemDataObj, unsigned long roundIndex) {
            UNUSED_PARAMETER(roundIndex);

            auto round = std::make_shared<TournamentRound>();
            round->load(itemDataObj);
            this->_rounds.push_back(round);
        });
}

void Tournament::save(obs_data_t *data) const
{
    obs_data_set_string(data, "name", this->_name.c_str());
    obs_data_set_int(data, "type", this->_type);
    obs_data_set_bool(data, "isStarted", this->_isStarted);

    OBSDataAutoRelease outputsData = obs_data_create();
    this->outputs.save(outputsData);
    obs_data_set_obj(data, "outputs", outputsData);

    ObsDataHelpers::saveArray<std::shared_ptr<Player>>(
        data, "players", this->_players,
        [](auto item, auto itemData) { item->save(itemData); });

    ObsDataHelpers::saveArray<std::shared_ptr<TournamentRound>>(
        data, "rounds", this->_rounds,
        [](auto item, auto itemData) { item->save(itemData); });
}

std::string Tournament::name() const
{
    return this->_name;
}

void Tournament::setName(const char *name)
{
    this->_name = name;
}

std::vector<std::shared_ptr<Player>> &Tournament::players()
{
    return this->_players;
}

void Tournament::setPlayers(std::vector<std::shared_ptr<Player>> &&__players)
{
    this->_players = __players;
}

Tournament::Type Tournament::type() const
{
    return this->_type;
}

void Tournament::setType(Tournament::Type __type)
{
    this->_type = __type;
}

std::vector<std::shared_ptr<TournamentRound>> &Tournament::rounds()
{
    return this->_rounds;
}

long long Tournament::duplicateRound(long long roundIndex)
{
    if (roundIndex < 0 || (unsigned long)roundIndex >= this->_rounds.size()) {
        return -1;
    }

    auto uRoundIndex = (unsigned long)roundIndex;

    std::shared_ptr<TournamentRound> roundToInsert =
        this->_rounds.at(uRoundIndex)->duplicate();
    Logger::log(
        "[Tournament::duplicateRound] duplicated round '%s' at index %d",
        roundToInsert->name().c_str(), uRoundIndex);

    uRoundIndex++;
    auto newRoundIndex = (long long)uRoundIndex;

    for (; uRoundIndex < this->_rounds.size(); uRoundIndex++) {
        auto temp = this->_rounds[uRoundIndex];
        this->_rounds[uRoundIndex] = roundToInsert;
        roundToInsert = temp;
    }

    this->_rounds.push_back(roundToInsert);

    return newRoundIndex;
}

bool Tournament::deleteRound(long long roundIndex)
{
    if (roundIndex < 0 || (unsigned long)roundIndex >= this->_rounds.size()) {
        return false;
    }
    auto uRoundIndex = (unsigned long)roundIndex;
    auto deletedRound = this->_rounds.at(uRoundIndex);
    this->_rounds.erase(this->_rounds.begin() + roundIndex);
    Logger::log("[Tournament::deleteRound] deleting round %s with index %d",
                deletedRound->name().c_str(), uRoundIndex);
    return true;
}

bool Tournament::isStarted() const
{
    return this->_isStarted;
}

void Tournament::setStarted(bool __isStarted)
{
    this->_isStarted = __isStarted;
}
