#pragma once

#include "src/data/tournament.hpp"
#include "src/ui/tabs/base-tab.hpp"
#include <QFrame>
#include <QLineEdit>
#include <QComboBox>
#include <QBoxLayout>

class CreateTournamentFrame : public QFrame {
    Q_OBJECT;

public:
    CreateTournamentFrame();
    ~CreateTournamentFrame();

signals:
    void tournamentCreated(std::shared_ptr<Tournament> newTournament);
    void tournamentTabCreated(BaseTab *newTab);

private:
    QLineEdit *_tournamentTitleLineEdit;
    QComboBox *_tournamentTypeComboBox;
    QVBoxLayout *_playerListLayout;
    bool endTournamentCreation();
    void addPlayer();
};
