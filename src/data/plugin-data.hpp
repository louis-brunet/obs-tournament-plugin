#pragma once

#include "src/data/tournament.hpp"
#include <memory>
#include <obs.hpp>
#include <obs-data.h>
#include <string>
#include <vector>

class TournamentPluginData;
// extern TournamentPluginData *pluginData;
extern std::unique_ptr<TournamentPluginData> pluginData;

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
    // --- (end) Save/load settings section  ---

    std::vector<std::shared_ptr<Tournament>> tournaments;

    std::vector<OBSWeakSource> textSources();
    std::vector<OBSWeakSource> imageSources();
    // std::vector<std::unique_ptr<Tournament>> tournaments;
};
