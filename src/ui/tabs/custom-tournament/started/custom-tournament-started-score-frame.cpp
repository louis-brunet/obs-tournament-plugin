#include "custom-tournament-started-score-frame.hpp"
#include "src/ui/components/button.hpp"
#include "src/ui/components/icon.hpp"
#include <QBoxLayout>
#include <QLabel>

CustomTournamentStartedScoreFrame::CustomTournamentStartedScoreFrame(
    unsigned char initialScore)
    : _score(initialScore)
{
    this->_incrementButton = new AppButton(
        "", AppIcon(AppIcon::Type::KeyboardArrowUp), AppButton::Style::Filled);
    this->_scoreLabel = new QLabel();
    this->_scoreLabel->setAlignment(Qt::AlignCenter);
    this->_decrementButton =
        new AppButton("", AppIcon(AppIcon::Type::KeyboardArrowDown),
                      AppButton::Style::Filled);

    this->setScore(initialScore);

    this->connect(this->_incrementButton, &QPushButton::clicked,
                  [this]() { this->setScore(this->_score + 1); });
    this->connect(this->_decrementButton, &QPushButton::clicked,
                  [this]() { this->setScore(this->_score - 1); });

    auto frameLayout = new QVBoxLayout();
    frameLayout->setContentsMargins(0, 0, 0, 0);
    frameLayout->addWidget(this->_incrementButton);
    frameLayout->addWidget(this->_scoreLabel);
    frameLayout->addWidget(this->_decrementButton);
    this->setLayout(frameLayout);
}

CustomTournamentStartedScoreFrame::~CustomTournamentStartedScoreFrame() {}

void CustomTournamentStartedScoreFrame::setEditable(bool isEditable)
{
    this->_incrementButton->setVisible(isEditable);
    this->_decrementButton->setVisible(isEditable);
}

void CustomTournamentStartedScoreFrame::setScore(unsigned char score)
{
    bool isChangedScore = score != this->_score;
    this->_score = score;
    this->updateScoreLabel();

    if (isChangedScore) {
        this->scoreChanged(score);
    }
}

void CustomTournamentStartedScoreFrame::updateScoreLabel()
{
    this->_scoreLabel->setText(std::to_string(this->_score).c_str());
}
