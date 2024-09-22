#pragma once

#include "src/data/match-reference.hpp"
#include "src/data/player-reference.hpp"
#include <QWidget>
#include <QComboBox>
#include <vector>

struct PlayerComboBoxData {
	enum Type {
		Unknown,
		Player,
		WinnerOf,
		LoserOf,
	};

	Type type = Type::Unknown;
	union {
		void *empty = nullptr;
		PlayerReference playerReference;
	};

	PlayerComboBoxData(Type type = Type::Unknown);
	PlayerComboBoxData(PlayerReference playerReference);
	~PlayerComboBoxData();
};

struct FromMatchComboBoxData {
	enum Type { Unknown, Match };

	Type type;
	union {
		void *empty = nullptr;
		MatchReference fromMatchReference;
	};

	FromMatchComboBoxData(Type type = Type::Unknown);
	FromMatchComboBoxData(MatchReference fromMatchReference);
    ~FromMatchComboBoxData();
};

class MatchParticipantInput : public QWidget {
	Q_OBJECT;

public:
	MatchParticipantInput();
	~MatchParticipantInput();

    // void setPlayers(const std::vector<> players);

private:
	QComboBox *playerComboBox;
	QComboBox *fromMatchComboBox;
};
