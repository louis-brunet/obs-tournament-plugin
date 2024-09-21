#include "custom-knockout-configuration-match-frame.hpp"
#include "src/ui/components/player-combo-box.hpp"
#include "src/plugin-support.h"

#include <QLabel>
#include <QGridLayout>

CustomKnockoutMatchFrame::CustomKnockoutMatchFrame(
	TournamentMatch *__tournamentMatch)
	: QFrame(),
	  _tournamentMatch(__tournamentMatch)
{
	obs_log(LOG_INFO,
		"[CustomKnockoutMatchFrame::CustomKnockoutMatchFrame] called");
	obs_log(LOG_INFO,
		"[CustomKnockoutMatchFrame::CustomKnockoutMatchFrame] _tournamentMatch->matchLabel()=%s",
		_tournamentMatch->matchLabel().c_str());
	// this->matchLabel = matchLabelText;
	// this->_tournamentMatch = __tournamentMatch;

	// auto matchFilterCallback = [this](TournamentMatch *match) {
	//     return match->matchLabel() != this->_tournamentMatch->matchLabel();
	// };
	this->_player1ComboBox = new PlayerComboBox(*this->_tournamentMatch);
	this->_player2ComboBox = new PlayerComboBox(*this->_tournamentMatch);

	this->connect(this->_player1ComboBox, &QComboBox::currentIndexChanged,
		      [this](int newIndex) {
			      obs_log(LOG_INFO,
				      "match %s, player 1 - new currentIndex is %d",
				      this->_tournamentMatch->matchLabel().c_str(),
				      newIndex);
			      auto comboBox = this->player1ComboBox();
			      auto participant =
				      comboBox->getPlayerData()
					      ->toTournamentMatchParticipant();
			      this->_tournamentMatch->setParticipant1(
				      participant);
		      });
	this->connect(this->_player2ComboBox, &QComboBox::currentIndexChanged,
		      [this](int newIndex) {
			      obs_log(LOG_INFO,
				      "match %s, player 2 - new currentIndex is %d",
				      this->_tournamentMatch->matchLabel().c_str(),
				      newIndex);
			      auto comboBox = this->player2ComboBox();
			      auto participant =
				      comboBox->getPlayerData()
					      ->toTournamentMatchParticipant();
			      this->_tournamentMatch->setParticipant2(
				      participant);
		      });

	auto matchLabel = this->_tournamentMatch->matchLabel();
	auto matchIdLabel = new QLabel(QString::fromStdString(matchLabel));
	matchIdLabel->setAlignment(Qt::AlignCenter);
	matchIdLabel->setMinimumWidth(60);

	auto newMatchLayout = new QGridLayout();
	newMatchLayout->setRowStretch(0, 0);
	newMatchLayout->setRowStretch(1, 0);
	newMatchLayout->setColumnStretch(0, 0);
	newMatchLayout->setColumnStretch(1, 1);
	newMatchLayout->addWidget(matchIdLabel, 0, 0, 2, 1, Qt::AlignCenter);
	newMatchLayout->addWidget(this->_player1ComboBox, 0, 1, Qt::AlignLeft);
	newMatchLayout->addWidget(this->_player2ComboBox, 1, 1, Qt::AlignLeft);

	this->setFrameStyle((int)QFrame::Panel | (int)QFrame::Raised);
	this->setLayout(newMatchLayout);
}

CustomKnockoutMatchFrame::~CustomKnockoutMatchFrame() {}

PlayerComboBox *CustomKnockoutMatchFrame::player1ComboBox()
{
	return this->_player1ComboBox;
}

PlayerComboBox *CustomKnockoutMatchFrame::player2ComboBox()
{
	return this->_player2ComboBox;
}

// TournamentMatch *CustomKnockoutMatchFrame::createTournamentMatch()
// {
// 	auto player1ComboBoxData = this->_player1ComboBox->getPlayerData();
// 	auto player2ComboBoxData = this->_player2ComboBox->getPlayerData();
//
// 	TournamentMatchParticipant *player1 =
// 		player1ComboBoxData->toTournamentMatchParticipant();
// 	TournamentMatchParticipant *player2 =
// 		player2ComboBoxData->toTournamentMatchParticipant();
//
//     if (player1 == nullptr || player2 == nullptr) {
//         return nullptr;
//     }
//
// 	return new TournamentMatch(player1, player2, this->matchLabel.c_str());
// }
