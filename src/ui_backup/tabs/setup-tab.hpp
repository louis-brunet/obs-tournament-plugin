#pragma once

#include <QBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>

class SetupTabFrame : public QFrame {
	Q_OBJECT;

public:
	SetupTabFrame(QTabWidget *tabWidget);
	~SetupTabFrame();

	// public slots:
	// 	void RefreshTable();
	// 	void ShowMatrix();

	// protected:
	// 	virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
	// TournamentBuilder *tournamentBuilder;
	QPushButton *showTournamentBuilderButton;
	QPushButton *finishTournamentBuilderButton;
	QPushButton *removePlayerButton;
	QWidget *tournamentBuilderFrame;
	QVBoxLayout *playerListLayout;
	QComboBox *tournamentTypeComboBox;
	QLineEdit *tournamentTitleLineEdit;
	QTabWidget *tabWidget;
	uint16_t playerCount;

	void addNewPlayerFrame();
	void initTournamentBuilder();
	bool finishTournamentBuilder();
	void removeNewPlayerFrame();
	void showTournamentBuilder(bool isVisible);
	void updateRemovePlayerButtonVisibility();
	// vector<string> getTournamentTypeChoices();
};
