#include "match.hpp"
#include <memory>
#include <obs.hpp>

Match::Match() {}

Match::~Match() {}

void Match::load(obs_data_t *data)
{
    // this->_participant1 = ;
    // this->_participant2 = nullptr;

    OBSDataAutoRelease participant1Data =
        obs_data_get_obj(data, "participant1");
    this->_participant1 = MatchParticipant::loadStatic(participant1Data);
    // if (participant1Data) {
    //     // this->_participant1 = std::make_shared<MatchParticipant>();
    //     // this->_participant1->load(participant1Data);
    // } else {
    //     this->_participant1 = std::make
    // }
}

void Match::save(obs_data_t *data) const
{
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
