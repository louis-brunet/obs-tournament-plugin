#include "create-player-frame.hpp"
#include "src/logger.hpp"
#include "src/ui/components/labeled-input.hpp"
#include "src/ui/components/line-edit.hpp"
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <obs-module.h>
#include <QPushButton>
#include <qboxlayout.h>

CreatePlayerFrame::CreatePlayerFrame() : QFrame()
{
    auto frameLayout = new QGridLayout();

    this->_playerNameLineEdit = new AppLineEdit();
    this->_playerNameLineEdit->setPlaceholderText(
        obs_module_text("setup.createTournament.playerNameInputPlaceholder"));
    auto playerNameInput = new AppLabeledInput(
        obs_module_text("setup.createTournament.playerNameInputLabel"),
        this->_playerNameLineEdit);

    this->_playerImagePreview = new QLabel();

    auto emptyPlayerImageLabelText =
        obs_module_text("setup.createTournament.playerImagePathEmpty");
    this->_playerImageLabel = new QLabel(emptyPlayerImageLabelText);
    auto playerImageOpenFileDialogButton = new QPushButton(
        obs_module_text("setup.createTournament.playerChooseImagePathButton"));
    this->connect(
        playerImageOpenFileDialogButton, &QPushButton::clicked,
        [this, emptyPlayerImageLabelText]() {
            auto playerImageFileDialog = new QFileDialog();
            playerImageFileDialog->setFileMode(QFileDialog::ExistingFile);
            playerImageFileDialog->setNameFilter("*.svg *.png *.jpg *.jpeg");
            playerImageFileDialog->exec();

            auto selected = playerImageFileDialog->selectedFiles();
            if (selected.size() == 0) {
                this->_playerImageLabel->setText(emptyPlayerImageLabelText);
                this->_imagePath = "";
                this->_playerImagePreview->setPixmap(QPixmap());
            } else {
                auto fileName = selected.at(0);
                auto pixmap = QPixmap(fileName).scaled(
                    80, 80, Qt::AspectRatioMode::KeepAspectRatio);

                this->_playerImageLabel->setText(fileName);
                Logger::log("selected file %s", fileName.toStdString().c_str());
                this->_imagePath = fileName.toStdString();
                this->_playerImagePreview->setPixmap(pixmap);
            }
        });

    auto playerImageInput = new QFrame();
    auto playerImageInputLayout = new QHBoxLayout();
    playerImageInput->setLayout(playerImageInputLayout);
    playerImageInputLayout->addWidget(
        new QLabel(
            obs_module_text("setup.createTournament.playerImageInputLabel")),
        0);
    playerImageInputLayout->addWidget(this->_playerImageLabel, 1);
    playerImageInputLayout->addWidget(this->_playerImagePreview, 0);
    playerImageInputLayout->addWidget(playerImageOpenFileDialogButton, 0);

    this->_playerDescriptionLineEdit = new AppLineEdit();
    this->_playerDescriptionLineEdit->setPlaceholderText(obs_module_text(
        "setup.createTournament.playerDescriptionInputPlaceholder"));
    auto playerDescriptionInput = new AppLabeledInput(
        obs_module_text("setup.createTournament.playerDescriptionInputLabel"),
        this->_playerDescriptionLineEdit);

    frameLayout->addWidget(playerNameInput);
    // frameLayout->addWidget(playerImageOpenFileDialogButton);
    frameLayout->addWidget(playerDescriptionInput);
    frameLayout->addWidget(playerImageInput);

    this->setLayout(frameLayout);
}

CreatePlayerFrame::~CreatePlayerFrame() {}

std::string CreatePlayerFrame::getPlayerName()
{
    return this->_playerNameLineEdit->text().toStdString();
}

std::string CreatePlayerFrame::getPlayerDescription()
{
    return this->_playerDescriptionLineEdit->text().toStdString();
}

std::string CreatePlayerFrame::getPlayerImagePath()
{
    return this->_imagePath;
}
