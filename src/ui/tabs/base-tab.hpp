#pragma once

#include <QBoxLayout>
#include <QScrollArea>

class BaseTab : public QScrollArea {
	Q_OBJECT;

public:
	BaseTab(std::string tabTitle);
	virtual ~BaseTab();
    const char *tabTitle() const;

protected:
	QVBoxLayout *_tabContentLayout;
	const std::string _tabTitle;
};
