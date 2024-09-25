#include "match.hpp"
#include "src/data/data-helpers.hpp"
#include <memory>
#include <obs.hpp>

Match::Match() {}

Match::~Match() {}

void Match::load(obs_data_t *data)
{
    this->state = ObsDataHelpers::getEnum<Match::State>(
        data, "state", Match::State::NotStarted);
    this->participant1Score = (unsigned char)ObsDataHelpers::getInt(data, "participant1Score", 0);
    this->participant2Score = (unsigned char)ObsDataHelpers::getInt(data, "participant2Score", 0);

    OBSDataAutoRelease participant1Data =
        obs_data_get_obj(data, "participant1");
    this->_participant1 = MatchParticipant::loadStatic(participant1Data);

    OBSDataAutoRelease participant2Data =
        obs_data_get_obj(data, "participant2");
    this->_participant2 = MatchParticipant::loadStatic(participant2Data);
}

void Match::save(obs_data_t *data) const
{
    obs_data_set_int(data, "state", this->state);
    obs_data_set_int(data, "participant1Score", this->participant1Score);
    obs_data_set_int(data, "participant2Score", this->participant2Score);

    OBSDataAutoRelease participant1Data = obs_data_create();
    this->_participant1->save(participant1Data);
    obs_data_set_obj(data, "participant1", participant1Data);

    OBSDataAutoRelease participant2Data = obs_data_create();
    this->_participant2->save(participant2Data);
    obs_data_set_obj(data, "participant2", participant2Data);
}

void Match::setParticipant1(std::shared_ptr<MatchParticipant> participant)
{
    this->_participant1 = participant;
}

void Match::setParticipant2(std::shared_ptr<MatchParticipant> participant)
{
    this->_participant2 = participant;
}

std::shared_ptr<MatchParticipant> Match::participant1()
{
    return this->_participant1;
}

std::shared_ptr<MatchParticipant> Match::participant2()
{
    return this->_participant2;
}

std::shared_ptr<Match> Match::duplicate() const
{
    auto newMatch = std::make_shared<Match>();
    newMatch->setParticipant1(this->_participant1->duplicate());
    newMatch->setParticipant2(this->_participant2->duplicate());
    return newMatch;
}
