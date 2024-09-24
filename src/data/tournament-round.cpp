#include "tournament-round.hpp"
#include "src/data/data-helpers.hpp"
#include "src/logger.hpp"

TournamentRound::TournamentRound()
{
    // TODO?
}

TournamentRound::~TournamentRound()
{
    // TODO?
}

void TournamentRound::load(obs_data_t *data)
{
    this->_name = ObsDataHelpers::getString(data, "name");

    ObsDataHelpers::iterateArray(data, "matches",
                                 [this](obs_data_t *matchData,
                                        unsigned long matchIndex) {
                                     UNUSED_PARAMETER(matchIndex);

                                     auto match = std::make_shared<Match>();
                                     match->load(matchData);
                                     this->_matches.push_back(match);
                                 });
}

void TournamentRound::save(obs_data_t *data) const
{
    obs_data_set_string(data, "name", this->_name.c_str());

    ObsDataHelpers::saveArray<std::shared_ptr<Match>>(
        data, "matches", this->_matches,
        [](auto match, auto matchData) { match->save(matchData); });
}

std::string TournamentRound::name() const
{
    return this->_name;
}

void TournamentRound::setName(std::string __name)
{
    this->_name = __name;
}

const std::vector<std::shared_ptr<Match>> &TournamentRound::matches() const
{
    return this->_matches;
}

void TournamentRound::addMatch(std::shared_ptr<Match> match)
{
    this->_matches.push_back(match);
}

long long TournamentRound::duplicateMatch(std::shared_ptr<Match> match)
{
    // FIXME: change parameter from Match to long long matchIndex, no need to compute index here?
    long long newMatchIndex = -1;
    unsigned long matchIndex = 0;
    while (matchIndex < this->_matches.size() &&
           this->_matches[matchIndex] != match) {
        matchIndex++;
    }

    if (matchIndex >= this->_matches.size()) {
        // TODO: not found
        return newMatchIndex;
    }
    Logger::log("duplicating match %d in round %s",
                matchIndex, this->_name.c_str());
    matchIndex++;

    auto matchToInsert = match->duplicate(); // std::make_shared<Match>(*match);
    // matchToInsert->setParticipant1(std::make_shared<MatchParticipant>(*match->participant1()));
    // matchToInsert->setParticipant2(std::make_shared<MatchParticipant>(*match->participant2()));
    //
    newMatchIndex = (long long)matchIndex;

    for (; matchIndex < this->_matches.size(); matchIndex++) {
        auto temp = this->_matches[matchIndex];
        this->_matches[matchIndex] = matchToInsert;
        matchToInsert = temp;
    }

    this->_matches.push_back(matchToInsert);

    // TODO: need to update all references to moved matches ?
    return newMatchIndex;
}

bool TournamentRound::deleteMatch(std::shared_ptr<Match> match)
{
    // Logger::log("[TournamentRound::deleteMatch] TODO");
    // auto matches = this->_tournamentRound->matches();
    unsigned long matchIndex = 0;

    while (matchIndex < this->_matches.size() &&
           this->_matches[matchIndex] != match) {
        matchIndex++;
    }

    if (matchIndex >= this->_matches.size()) {
        // TODO: not found
        return false;
    }
    Logger::log("deleting match %d in round %s (TODO update references)",
                matchIndex, this->name().c_str());

    this->_matches.erase(this->_matches.begin() + (long long)matchIndex);

    // TODO: need to update all references to moved matches ?
    return true;
}

bool TournamentRound::swapPrevious(long long matchIndex) {
    if (matchIndex <= 0 || (unsigned long)matchIndex >= this->_matches.size()) {
        return false;
    }

    unsigned long uMatchIndex = (unsigned long)matchIndex;
    auto tempMatch = this->_matches.at(uMatchIndex);
    this->_matches[uMatchIndex] = this->_matches.at(uMatchIndex - 1);
    this->_matches[uMatchIndex - 1] = tempMatch;
    return true;
}

bool TournamentRound::swapNext(long long matchIndex) {
    if (matchIndex < 0 || (unsigned long)matchIndex >= this->_matches.size() - 1) {
        return false;
    }

    unsigned long uMatchIndex = (unsigned long)matchIndex;
    auto tempMatch = this->_matches.at(uMatchIndex);
    this->_matches[uMatchIndex] = this->_matches.at(uMatchIndex + 1);
    this->_matches[uMatchIndex + 1] = tempMatch;
    return true;
}

std::shared_ptr<TournamentRound> TournamentRound::duplicate() const
{
    auto newRound = std::make_shared<TournamentRound>();
    newRound->_name = this->_name;
    for (auto match : this->_matches) {
        newRound->_matches.push_back(match->duplicate());
    }
    return newRound;
}
