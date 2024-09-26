#pragma once

#include "src/data/match-reference.hpp"
#include "src/data/tournament-reference.hpp"
#include "src/ui/tabs/custom-tournament/started/source-combo-box.hpp"
#include <QFrame>
#include <QComboBox>
#include <QGroupBox>

class CustomTournamentStartedOutputsFrame : public QGroupBox {
    Q_OBJECT;

public:
    CustomTournamentStartedOutputsFrame();
    ~CustomTournamentStartedOutputsFrame();

    void setTournament(TournamentReference tournamentReference);

private:
    QComboBox *_currentMatchComboBox;
    SourceComboBox *_participant1NameInput;
    SourceComboBox *_participant2NameInput;
    SourceComboBox *_participant1ImageInput;
    SourceComboBox *_participant2ImageInput;
    SourceComboBox *_participant1ScoreInput;
    SourceComboBox *_participant2ScoreInput;

    // void setCurrentMatchOutputs(MatchReference *currentMatchReference);
    void updateOutputSources();
};
