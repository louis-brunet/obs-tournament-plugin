#pragma once

#include "src/model/match-reference.hpp"
#include "src/model/player-reference.hpp"
#include "src/model/tournament-match.hpp"
#include "src/model/tournament-match-participant.hpp"

#include <QComboBox>

struct PlayerComboBoxEmpty {};

struct PlayerComboBoxStaticPlayer {
	// Player *player;
	// unsigned index;
    PlayerReference playerReference;
};

struct PlayerComboBoxWinnerOfMatch {
	// TournamentMatch *match;
	// long long matchIndex;
	MatchReference matchReference;
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
	// FIXME: replacing `MatchReference *` with `MatchReference` implicitly deletes these constructors
	// PlayerComboBoxData(PlayerComboBoxData &&) = default;
	// PlayerComboBoxData(const PlayerComboBoxData &) = default;
	// PlayerComboBoxData &operator=(PlayerComboBoxData &&) = default;
	// PlayerComboBoxData &operator=(const PlayerComboBoxData &) = default;
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
	// void setPlayerOptions(const std::vector<Player *> players,
	void setPlayerOptions(const std::vector<PlayerReference> &players,
			      const std::vector<MatchReference> matches);
	// const std::vector<TournamentMatch *> matches);
	const PlayerComboBoxData *getPlayerData() const;

private:
	std::function<bool(TournamentMatch *)> matchFilterCallback;
	// bool (*matchFilterCallback)(TournamentMatch * match);
};
