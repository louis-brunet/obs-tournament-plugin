#pragma once

#include <QFrame>
#include <QLabel>
#include <QLineEdit>

class CreatePlayerFrame : public QFrame {
    Q_OBJECT;

public:
    CreatePlayerFrame();
    ~CreatePlayerFrame();

    std::string getPlayerName();
    std::string getPlayerImagePath();
    std::string getPlayerDescription();

private:
    QLabel *_playerImageLabel;
    QLabel *_playerImagePreview;
    QLineEdit *_playerNameLineEdit;
    QLineEdit *_playerDescriptionLineEdit;

    std::string _imagePath;
};
