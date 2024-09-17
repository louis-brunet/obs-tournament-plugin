#pragma once

#include "src/model/player.hpp"
#include "src/model/tournament-match.hpp"
#include "src/model/tournament-match-participant.hpp"

#include <QComboBox>

struct PlayerComboBoxEmpty {};

struct PlayerComboBoxStaticPlayer {
	Player *player;
	unsigned index;
};

struct PlayerComboBoxWinnerOfMatch {
	TournamentMatch *match;
    long long matchIndex;
};

struct PlayerComboBoxData {

public:
	enum Type {
		Empty = -1,
		StaticPlayer = 0,
		WinnerOfMatch,
	};

    PlayerComboBoxData::Type dataType;
	union {
		PlayerComboBoxEmpty empty;
		PlayerComboBoxStaticPlayer staticPlayer;
		PlayerComboBoxWinnerOfMatch winnerOfMatch;
	};

	PlayerComboBoxData();
	PlayerComboBoxData(PlayerComboBoxData &&) = default;
	PlayerComboBoxData(const PlayerComboBoxData &) = default;
	PlayerComboBoxData &operator=(PlayerComboBoxData &&) = default;
	PlayerComboBoxData &operator=(const PlayerComboBoxData &) = default;
	~PlayerComboBoxData();
	TournamentMatchParticipant *toTournamentMatchParticipant() const;
};

class PlayerComboBox : public QComboBox {
	Q_OBJECT;

public:
	// PlayerComboBox(bool (*__matchFilterCallback)(TournamentMatch *));
	// PlayerComboBox(std::function<bool(TournamentMatch *)>);
	PlayerComboBox(const TournamentMatch &tournamentMatch);
	~PlayerComboBox();
	// void setMatchList(std::vector<TournamentMatch> matches);
	// void setPlayerList(std::vector<Player> players);
	void setPlayerOptions(const std::vector<Player *> players,
			      const std::vector<TournamentMatch *> matches);
	const PlayerComboBoxData *getPlayerData() const;

private:
	std::function<bool(TournamentMatch *)> matchFilterCallback;
	// bool (*matchFilterCallback)(TournamentMatch * match);
};
