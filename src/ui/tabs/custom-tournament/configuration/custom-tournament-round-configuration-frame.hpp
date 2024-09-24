#pragma once

#include "src/data/match-reference-remap.hpp"
#include "src/data/tournament-round-reference.hpp"
#include "src/data/tournament-round.hpp"
#include <QFrame>
#include <QBoxLayout>

class CustomTournamentRoundConfigurationFrame : public QFrame {
    Q_OBJECT;

public:
    QVBoxLayout *matchListLayout;

    CustomTournamentRoundConfigurationFrame(
        std::shared_ptr<TournamentRound> tournamentRound,
        TournamentRoundReference roundReference);
    ~CustomTournamentRoundConfigurationFrame();

    // void setPlayers(const std::vector<PlayerReference> &playerReferences);
    // void setMatches(const std::vector<MatchReference> &matchReferences);

signals:
    void matchCountChanged(const MatchReferenceRemap &matchReferenceRemap);

    void duplicateRoundClicked();
    void deleteRoundClicked();
    // void moveUpClicked();
    // void moveDownClicked();

private:
    std::shared_ptr<TournamentRound> _tournamentRound;
    TournamentRoundReference _roundReference;

    MatchReference addNewMatch();
    void addExistingMatch(std::shared_ptr<Match> match,
                          unsigned long matchIndexInRound);
    // void duplicateRound();
    // void deleteRound();
    void refreshMatchList();
};
