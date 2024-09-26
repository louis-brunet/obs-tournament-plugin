#pragma once

#include "src/data/match-reference-remap.hpp"
#include "src/data/match-reference.hpp"
#include "src/data/player-reference.hpp"
#include "src/data/tournament-reference.hpp"
#include "src/data/tournament-round.hpp"
#include <QFrame>
#include <QBoxLayout>

class CustomTournamentConfigurationFrame : public QFrame {
    Q_OBJECT;

public:
    CustomTournamentConfigurationFrame(TournamentReference tournamentReference);
    ~CustomTournamentConfigurationFrame();

signals:
    void tournamentConfigured();

private:
    // std::shared_ptr<Tournament> _tournament;
    TournamentReference _tournamentReference;
    QVBoxLayout *_roundListLayout;

    void addNewRound();
    void addExistingRound(std::shared_ptr<TournamentRound> round,
                          unsigned long roundIndex);
    void refreshRoundList(
        unsigned long startingRoundIndex = 0,
        const MatchReferenceRemap &remap = MatchReferenceRemapNone());
    void
    updatePlayerChoices(const MatchReferenceRemap
                            &remap); //unsigned long startingRoundIndex = 0);
    void endTournamentConfiguration();
};
