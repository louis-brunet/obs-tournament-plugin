#include "debug-frame.hpp"
#include "src/data/plugin-data.hpp"
#include "src/logger.hpp"
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <obs-frontend-api.h>
#include <obs.h>
#include <obs.hpp>

using namespace Logger;

DebugFrame::DebugFrame(std::function<void()> onResetDataCallback) : QFrame()
{
    auto frameLayout = new QVBoxLayout();

    auto groupBox = new QGroupBox("DEBUG");
    auto groupBoxLayout = new QHBoxLayout();
    groupBox->setLayout(groupBoxLayout);
    frameLayout->addWidget(groupBox);

    auto logDataButton = new QPushButton("log data");
    groupBoxLayout->addWidget(logDataButton, 0);
    this->connect(logDataButton, &QPushButton::clicked, []() {
        log(LOG_INFO, "Plugin data:\n%s", pluginData->toJson().c_str());

        // TODO: remove this
        auto sources = pluginData->textSources();
        log("FOUND %d text sources", sources.size());
    });

    auto clearDataButton = new QPushButton("clear data");
    groupBoxLayout->addWidget(clearDataButton, 0);
    this->connect(clearDataButton, &QPushButton::clicked,
                  [this, onResetDataCallback]() {
                      this->clearData();
                      onResetDataCallback();
                  });

    auto unstartTournamentsButton = new QPushButton("unstart");
    groupBoxLayout->addWidget(unstartTournamentsButton, 0);
    this->connect(unstartTournamentsButton, &QPushButton::clicked, []() {
        for (auto tournament : pluginData->tournaments) {
            tournament->setStarted(false);
        }
    });

    this->setLayout(frameLayout);
}

DebugFrame::~DebugFrame() {}

void DebugFrame::clearData()
{
    if (pluginData) {
        auto jsonData = pluginData->toJson();
        log(LOG_INFO,
            "[DebugFrame::clearData] deleting plugin data, current data was: %s",
            jsonData.c_str());
        freeTournamentPluginData();
    }
    initTournamentPluginData();
    log(LOG_INFO, "[DebugFrame::clearData] plugin data is now: %s",
        pluginData->toJson().c_str());
}
