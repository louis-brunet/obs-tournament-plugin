#pragma once

#include "src/data/match-reference.hpp"
#include "src/data/match.hpp"
#include "src/ui/tabs/custom-tournament/configuration/match-participant-input.hpp"
#include <QFrame>
#include <QBoxLayout>

class CustomTournamentMatchConfigurationFrame : public QFrame {
    Q_OBJECT;

public:
    MatchParticipantInput *participant1Input;
    MatchParticipantInput *participant2Input;

    CustomTournamentMatchConfigurationFrame(std::shared_ptr<Match> match,
                                            MatchReference matchReference);
    ~CustomTournamentMatchConfigurationFrame();

    // void setPlayers(const std::vector<PlayerReference> &playerReferences);
    // void setMatches(const std::vector<MatchReference> &matchReferences);

signals:
    void duplicateMatchClicked();
    void deleteMatchClicked();
    void swapPreviousClicked();
    void swapNextClicked();
    // void duplicateMatch(std::shared_ptr<Match> match);

private:
    std::shared_ptr<Match> _match;
    // void duplicateMatch();
    // void deleteMatch();
};
