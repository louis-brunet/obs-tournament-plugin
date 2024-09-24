#pragma once

#include "src/data/tournament-reference.hpp"
#include "src/ui/tabs/base-tab.hpp"
#include <QTabWidget>

class CustomTournamentTab : public BaseTab {
public:
    CustomTournamentTab(TournamentReference tournamentReference);
    ~CustomTournamentTab();

private:
};

