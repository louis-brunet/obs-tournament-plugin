#include "custom-tournament-match-configuration-frame.hpp"
#include "src/ui/components/icon.hpp"
#include "src/ui/tabs/custom-tournament/configuration/match-participant-input.hpp"
#include <obs-module.h>
#include <QLabel>
#include <QPushButton>

CustomTournamentMatchConfigurationFrame::CustomTournamentMatchConfigurationFrame(
	std::shared_ptr<Match> match)
	: _match(match)
{
    // this->_participant1ComboBox = new PlayerComboBox();
    // this->_participant2ComboBox = new PlayerComboBox();
    auto participant1Input = new MatchParticipantInput();
    auto participant2Input = new MatchParticipantInput();

    auto duplicateMatchButton = new QPushButton(AppIcon(AppIcon::Type::Copy), "");
    duplicateMatchButton->setToolTip(obs_module_text("customTournament.configuration.duplicateMatchButtonTooltip"));
	this->connect(duplicateMatchButton, &QPushButton::clicked,
		      [this]() { this->duplicateMatch(); });

    auto deleteMatchButton = new QPushButton(AppIcon(AppIcon::Type::Delete), "");
    deleteMatchButton->setToolTip(obs_module_text("customTournament.configuration.deleteMatchButtonTooltip"));
	this->connect(deleteMatchButton, &QPushButton::clicked,
		      [this]() { this->deleteMatch(); });

	auto frameLayout = new QHBoxLayout();
	// frameLayout->addWidget(new QLabel("TODO match config frame"));
	frameLayout->addWidget(participant1Input, 1);
    frameLayout->addWidget(new QLabel(obs_module_text("customTournament.configuration.versus")), 0);
	frameLayout->addWidget(participant2Input, 1);
	frameLayout->addWidget(duplicateMatchButton, 0);
	frameLayout->addWidget(deleteMatchButton, 0);
	this->setLayout(frameLayout);
}

CustomTournamentMatchConfigurationFrame::
	~CustomTournamentMatchConfigurationFrame()
{
}
