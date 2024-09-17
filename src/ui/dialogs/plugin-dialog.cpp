#include "plugin-dialog.hpp"
#include "obs-module.h"
#include "src/model/custom-knockout-tournament.hpp"
#include "src/model/plugin-data.hpp"
#include "src/plugin-support.h"
#include "src/ui/dialogs/base-dialog.hpp"
#include "src/ui/dialogs/error-dialog.hpp"
#include "src/ui/tabs/custom-knockout-tab/custom-knockout-tab.hpp"
#include "src/ui/tabs/setup-tab.hpp"

#include <QLabel>
#include <obs-frontend-api.h>

using namespace std;

int plugin_dialog_width = 0;
int plugin_dialog_height = 0;
int pluginDialogMinWidth = 600;
int pluginDialogMinHeight = 400;
// TournamentPluginDialog *TournamentPluginDialog::instance = nullptr;
//
// TournamentPluginDialog *TournamentPluginDialog::getInstance()
// {
// 	if (!TournamentPluginDialog::instance) {
// 		TournamentPluginDialog::instance = new TournamentPluginDialog(
// 			PLUGIN_VERSION,
// 			reinterpret_cast<QMainWindow *>(
// 				obs_frontend_get_main_window()));
// 	}
//
// 	return TournamentPluginDialog::instance;
// }

TournamentPluginDialog::TournamentPluginDialog(std::string pluginVersionStr,
					       QMainWindow *parent)
	: BaseDialog(parent, obs_module_text("TournamentPluginName"),
		     pluginDialogMinWidth, pluginDialogMinHeight)
{
	this->pluginVersion = pluginVersionStr;
	this->tabsWidget = new QTabWidget();
    // this->tabsWidget->setTabsClosable(true);

	auto setupTab = new SetupTabFrame(this->tabsWidget);
	this->tabsWidget->addTab(setupTab, obs_module_text("SetupTabTitle"));

	this->setStyleSheet("QLineEdit[value=\"\"]{"
			    "    color: gray;" //TEXTHOLDER COLOR
			    "}");

	// auto *testTextSourceCombo = new QComboBox();
	//
	// // testTextSourceCombo->setEditable(true);
	// // auto *testComboCompleter = testTextSourceCombo->completer();
	// // testComboCompleter->setCaseSensitivity(Qt::CaseInsensitive);
	// // testComboCompleter->setFilterMode(Qt::MatchContains);
	// // testComboCompleter->setCompletionMode(QCompleter::PopupCompletion);
	//
	// testTextSourceCombo->addItem("", QByteArray(""));
	// testTextSourceCombo->addItem("Test item", QByteArray("Test item"));
	//
	// struct obs_frontend_source_list sceneList = {};
	// obs_frontend_get_scenes(&sceneList);
	//
	// auto sceneEnumItemsCallback = [](obs_scene_t *,
	// 				 obs_sceneitem_t *sceneItem,
	// 				 void *callbackData) -> bool {
	// 	auto *itemSource = obs_sceneitem_get_source(sceneItem);
	// 	auto sourceName = obs_source_get_name(itemSource);
	// 	obs_log(LOG_INFO,
	// 		"[TournamentPluginDialog.sceneEnumItemsCallback] sourceName='%s'",
	// 		sourceName);
	// 	auto *testTextSourceComboPtr =
	// 		reinterpret_cast<QComboBox *>(callbackData);
	// 	testTextSourceComboPtr->addItem(sourceName,
	// 					QByteArray(sourceName));
	// 	obs_log(LOG_INFO,
	// 		"[TournamentPluginDialog.sceneEnumItemsCallback] added '%s'",
	// 		sourceName);
	//
	// 	return true;
	// };
	//
	// for (size_t idx = 0; idx < sceneList.sources.num; idx++) {
	// 	auto *sceneSource = sceneList.sources.array[idx];
	// 	auto sourceName = obs_source_get_name(sceneSource);
	// 	obs_log(LOG_INFO, "[TournamentPluginDialog] scene name: %s",
	// 		sourceName);
	// 	auto *scene = obs_get_scene_by_name(sourceName);
	//
	// 	obs_scene_enum_items(scene, sceneEnumItemsCallback,
	// 			     testTextSourceCombo);
	//
	// 	obs_scene_release(scene);
	// }
	// obs_frontend_source_list_free(&sceneList);
	//
	// auto *testButton = new QPushButton("test");
	// this->connect(testButton, &QPushButton::clicked, [testTextSourceCombo]() {
	// 	// auto selectedIndex = testTextSourceCombo->currentIndex();
	// 	auto selectedTextString =
	// 		testTextSourceCombo->currentText().toStdString();
	// 	auto selectedText = selectedTextString.c_str();
	//
	// 	obs_log(LOG_INFO, "selected text '%s'", selectedText);
	//
	// 	auto *selectedSource = obs_get_source_by_name(selectedText);
	// 	auto *sourceSettings = obs_source_get_settings(selectedSource);
	// 	obs_data_set_string(sourceSettings, "text", "CHANGED TEXT");
	//
	// 	obs_source_update(selectedSource, sourceSettings);
	//
	// 	obs_data_release(sourceSettings);
	// 	obs_source_release(selectedSource);
	// });
	//
	// auto *testTabLayout = new QVBoxLayout();
	// testTabLayout->addWidget(testTextSourceCombo, 0, Qt::AlignTop);
	// testTabLayout->addWidget(testButton, 0, Qt::AlignTop);
	//
	// auto *testTab = new QFrame();
	// testTab->setLayout(testTabLayout);

	QPushButton *closeButton =
		new QPushButton(QString::fromUtf8(obs_module_text("Close")));

	string creditsLabelPluginLinkOpenTag =
		"<a href=\"https://github.com/louis-brunet/obs-tournament-plugin\">";
	string creditsLabelPluginLinkText =
		obs_module_text("TournamentPluginName");
	string creditsLabelPluginLinkCloseTag = "</a>";
	string creditsLabelPluginLink = creditsLabelPluginLinkOpenTag +
					creditsLabelPluginLinkText +
					creditsLabelPluginLinkCloseTag;

	string creditsLabelText =
		creditsLabelPluginLink + " (v" + this->pluginVersion +
		") by <a href=\"https://github.com/louis-brunet\">Louis Brunet</a>";

	QHBoxLayout *bottomLayout = new QHBoxLayout;
	bottomLayout->addWidget(
		new QLabel(QString::fromStdString(creditsLabelText)), 0,
		Qt::AlignLeft);
	bottomLayout->addWidget(closeButton, 0, Qt::AlignRight);
	bottomLayout->setStretch(0, 1);
	connect(closeButton, &QPushButton::clicked,
		[this]() { this->close(); });

	auto vlayout = new QVBoxLayout;
	vlayout->setContentsMargins(11, 11, 11, 11);
	vlayout->setAlignment(Qt::AlignTop);
	vlayout->addWidget(this->tabsWidget);
	vlayout->addLayout(bottomLayout);
	this->setLayout(vlayout);

	if (plugin_dialog_width > pluginDialogMinWidth &&
	    plugin_dialog_height > pluginDialogMinHeight) {
		this->resize(plugin_dialog_width, plugin_dialog_height);
	}

	this->loadData(pluginData);
}

TournamentPluginDialog::~TournamentPluginDialog()
{
	auto size = this->size();
	plugin_dialog_width = size.width();
	plugin_dialog_height = size.height();
	// obs_frontend_source_list_free(&scenes);
	// obs_frontend_source_list_free(&transitions);
}

void TournamentPluginDialog::loadData(const TournamentPluginData *_pluginData)
{
	obs_log(LOG_INFO,
		"TournamentPluginDialog::loadData called, pluginData ptr is %p",
		_pluginData);

	for (auto tournament : _pluginData->tournaments) {
		QWidget *tournamentTab;
		const char *tournamentTabTitle;
		obs_log(LOG_INFO,
			"TournamentPluginDialog::loadData tournament ptr is %p",
			tournament);

		switch (tournament->type) {
		case Tournament::Type::SingleEliminationKnockoutTournamentType:
			throw new std::runtime_error(
				"TODO: SingleEliminationKnockoutTournament");
			// (new ErrorDialog(
			// 	 this,
			// 	 "TODO: SingleEliminationKnockoutTournament"))
			// 	->show();
			// return;
			break;
            case Tournament::Type::CustomKnockoutTournamentType:
			tournamentTab = new CustomKnockoutTabFrame(reinterpret_cast<CustomKnockoutTournament *>(tournament));
			tournamentTabTitle =
				obs_module_text("CustomKnockoutTabTitle");
			break;

		default:
			throw new std::runtime_error(
				"unrecognized tournament type");
		}

		obs_log(LOG_INFO,
			"TournamentPluginDialog::loadData restoring tournament tab");
		this->tabsWidget->addTab(tournamentTab, tournamentTabTitle);
	}
}
