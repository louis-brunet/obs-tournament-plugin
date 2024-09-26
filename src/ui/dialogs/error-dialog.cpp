#include "error-dialog.hpp"
#include <obs-module.h>

#include <QBoxLayout>
#include <QButtonGroup>
#include <QLabel>
#include <QPushButton>

static const int ERROR_DIALOG_MINIMUM_WIDTH = 400;
static const int ERROR_DIALOG_MINIMUM_HEIGHT = 100;

ErrorDialog::ErrorDialog(QWidget *parent, const char *message)
    : BaseDialog(parent, obs_module_text("error.dialogTitle"),
                 ERROR_DIALOG_MINIMUM_WIDTH, ERROR_DIALOG_MINIMUM_HEIGHT)
{
    auto dialogLayout = new QVBoxLayout();
    dialogLayout->setAlignment(Qt::AlignVCenter);

    auto errorMessageLabel = new QLabel(message);
    dialogLayout->addWidget(errorMessageLabel);

    auto closeButton = new QPushButton(obs_module_text("Close"));
    this->connect(closeButton, &QPushButton::clicked,
                  [this]() { this->close(); });

    auto buttonLayout = new QHBoxLayout();
    buttonLayout->setAlignment(Qt::AlignRight);
    buttonLayout->addWidget(closeButton);
    dialogLayout->addLayout(buttonLayout, Qt::AlignBottom);

    this->setLayout(dialogLayout);
}

ErrorDialog::~ErrorDialog() {}
