#include "match-participant-input.hpp"
#include <QBoxLayout>

MatchParticipantInput::MatchParticipantInput()
{
	this->playerComboBox = new QComboBox();
	auto playerEmptyData = new PlayerComboBoxData();
	this->playerComboBox->addItem("", (long long)playerEmptyData);

	this->fromMatchComboBox = new QComboBox();
	auto fromMatchEmptyData = new FromMatchComboBoxData();
	this->fromMatchComboBox->addItem("", (long long)fromMatchEmptyData);
	this->fromMatchComboBox->setVisible(false);

	auto frameLayout = new QVBoxLayout();
	frameLayout->addWidget(this->playerComboBox);
	frameLayout->addWidget(this->fromMatchComboBox);
	this->setLayout(frameLayout);
}

MatchParticipantInput::~MatchParticipantInput() {}

PlayerComboBoxData::PlayerComboBoxData(PlayerComboBoxData::Type _type): type(_type) {}

PlayerComboBoxData::~PlayerComboBoxData() {}

FromMatchComboBoxData::FromMatchComboBoxData(FromMatchComboBoxData::Type _type): type(_type) {}

FromMatchComboBoxData::~FromMatchComboBoxData() {}
