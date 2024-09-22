#pragma once

#include "src/model/tournament.hpp"
#include <obs-data.h>
#include <vector>

class TournamentPluginData;
extern TournamentPluginData *pluginData;

void initTournamentPluginData();
void freeTournamentPluginData();

class TournamentPluginData {
public:
    TournamentPluginData();
    ~TournamentPluginData();

    // --- Save/load settings section (start) ---
    void loadSettings(obs_data_t *dataObj);
    void saveSettings(obs_data_t *dataObj);

    std::string toJson();
    // --- Save/load settings section (end) ---

    std::vector<Tournament *> tournaments;
};
