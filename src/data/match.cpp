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
