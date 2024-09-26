#pragma once

#include <QFrame>
#include <QLabel>
#include <QPushButton>

class CustomTournamentStartedScoreFrame : public QFrame {
    Q_OBJECT;

public:
    CustomTournamentStartedScoreFrame(unsigned char initialScore = 0);
    ~CustomTournamentStartedScoreFrame();

    void setEditable(bool isEditable);

signals:
    void scoreChanged(unsigned char newScore);

private:
    QPushButton *_decrementButton;
    QPushButton *_incrementButton;
    QLabel *_scoreLabel;
    unsigned char _score = 0;

    void setScore(unsigned char score);
    void updateScoreLabel();
};
