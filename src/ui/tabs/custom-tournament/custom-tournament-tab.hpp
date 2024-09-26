#pragma once

#include "src/data/tournament-reference.hpp"
#include "src/ui/tabs/base-tab.hpp"
#include "src/ui/tabs/custom-tournament/configuration/custom-tournament-configuration-frame.hpp"
#include "src/ui/tabs/custom-tournament/started/custom-tournament-started-frame.hpp"

class CustomTournamentTab : public BaseTab {
public:
    CustomTournamentTab(TournamentReference tournamentReference);
    ~CustomTournamentTab();

private:
    CustomTournamentConfigurationFrame *_configurationFrame;
    CustomTournamentStartedFrame *_startedFrame;

    void endTournamentConfiguration(TournamentReference tournamentReference);
};
