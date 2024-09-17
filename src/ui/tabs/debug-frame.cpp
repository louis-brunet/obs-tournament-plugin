#include "debug-frame.hpp"
#include "src/model/plugin-data.hpp"
#include "src/plugin-support.h"
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>

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
        obs_log(LOG_INFO, "Plugin data:\n%s",
                pluginData->toJson().c_str());
    });

	auto clearDataButton = new QPushButton("clear data");
	groupBoxLayout->addWidget(clearDataButton, 0);
	this->connect(clearDataButton, &QPushButton::clicked,
		      [this, onResetDataCallback]() {
			      this->clearData();
			      onResetDataCallback();
		      });


	this->setLayout(frameLayout);
}

DebugFrame::~DebugFrame() {}

void DebugFrame::clearData()
{
	if (pluginData) {
		auto jsonData = pluginData->toJson();
		obs_log(LOG_INFO,
			"[DebugFrame::clearData] deleting plugin data, current data was: %s",
			jsonData.c_str());
		// pluginData->clearData();
		delete pluginData;
	}
	pluginData = new TournamentPluginData();
	obs_log(LOG_INFO, "[DebugFrame::clearData] plugin data is now: %s",
		pluginData->toJson().c_str());
}
