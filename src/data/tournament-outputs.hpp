#pragma once

#include "src/data/match-reference.hpp"
#include <obs-data.h>
#include <string>

class TournamentSourceOutput {
public:
    std::string sourceUuid = "";

    virtual void load(obs_data_t *data);
    virtual void save(obs_data_t *data) const;

    void setSourceText(const char *text);
    void setSourceImageFile(const char *imageFilePath);

private:
    void setSourceSettingString(const char *settingSame,
                                const char *settingValue);
};

// class TournamentTextSourceOutput : public TournamentSourceOutput {
// public:
//     void load(obs_data_t *data);
//     void save(obs_data_t *data) const;
// };
//
// class TournamentImageSourceOutput : public TournamentSourceOutput {
// public:
//     void load(obs_data_t *data);
//     void save(obs_data_t *data) const;
// };

class TournamentOutputs {
public:
    MatchReference currentMatch = MatchReference();
    MatchReference upcomingMatch = MatchReference();

    TournamentSourceOutput participant1Name = TournamentSourceOutput();
    TournamentSourceOutput participant1Image = TournamentSourceOutput();
    TournamentSourceOutput participant1Score = TournamentSourceOutput();
    TournamentSourceOutput participant1Description = TournamentSourceOutput();

    TournamentSourceOutput participant2Name = TournamentSourceOutput();
    TournamentSourceOutput participant2Image = TournamentSourceOutput();
    TournamentSourceOutput participant2Score = TournamentSourceOutput();
    TournamentSourceOutput participant2Description = TournamentSourceOutput();
    // TournamentTextSourceOutput participant1Name = TournamentTextSourceOutput();
    // TournamentTextSourceOutput participant2Name = TournamentTextSourceOutput();
    // TournamentImageSourceOutput participant1Image = TournamentImageSourceOutput();
    // TournamentImageSourceOutput participant2Image = TournamentImageSourceOutput();

    TournamentOutputs();
    ~TournamentOutputs();

    void load(obs_data_t *data);
    void save(obs_data_t *data) const;
};
