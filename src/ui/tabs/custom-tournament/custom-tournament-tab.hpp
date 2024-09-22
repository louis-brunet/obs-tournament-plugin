#pragma once

#include "src/data/tournament.hpp"
#include "src/ui/tabs/base-tab.hpp"
#include <QTabWidget>

class CustomTournamentTab : public BaseTab {
public:
    CustomTournamentTab(std::shared_ptr<Tournament> tournament);
    ~CustomTournamentTab();

private:
};

