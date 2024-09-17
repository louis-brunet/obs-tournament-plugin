#pragma once

#include "src/model/tournament-match.hpp"
#include "src/ui/tabs/custom-knockout-tab/custom-knockout-running-all-matches-frame.hpp"
#include <QFrame>

class CustomKnockoutRunningFrame : public QFrame {
public:
    CustomKnockoutRunningFrame();
    ~CustomKnockoutRunningFrame();
    void setMatches(std::vector<TournamentMatch *> matches);

private:
    CustomKnockoutRunningAllMatchesFrame *allMatchesWidget;
};
