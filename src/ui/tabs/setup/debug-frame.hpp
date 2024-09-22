#pragma once

#include <QFrame>

class DebugFrame : public QFrame {
public:
	DebugFrame(std::function<void()> onResetDataCallback);
	~DebugFrame();

private:
	void clearData();
};
