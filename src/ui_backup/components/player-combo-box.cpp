#include "player-combo-box.hpp"
#include "src/model/match-reference.hpp"
#include "src/model/player-reference.hpp"
#include "src/model/tournament-match-participant-player.hpp"
#include "src/model/tournament-match-participant-unknown.hpp"
#include "src/model/tournament-match-participant-winner-of-match.hpp"
#include "src/plugin-support.h"

#include <obs-module.h>
#include <QCompleter>

PlayerComboBoxData::PlayerComboBoxData()
{
	this->dataType = PlayerComboBoxData::Type::Empty;
	this->empty = {};
}

TournamentMatchParticipant *
PlayerComboBoxData::toTournamentMatchParticipant() const
{
	TournamentMatchParticipant *participant;

	obs_log(LOG_DEBUG,
		"[PlayerComboBoxData::toTournamentMatchParticipant] dataType=%d",
		this->dataType);

	switch (this->dataType) {
	case PlayerComboBoxData::Type::Empty: {
		participant = new TournamentMatchParticipantUnknown();
		break;
	}
	case PlayerComboBoxData::Type::StaticPlayer: {
		participant = new TournamentMatchParticipantPlayer(
			this->staticPlayer.playerReference);
		break;
	}
	case PlayerComboBoxData::Type::WinnerOfMatch: {
		// TournamentReference tournamentReference(tournamentIndex);
		// MatchReference winnerOfMatchReference(tournamentReference, this->winnerOfMatch.matchIndex);
		participant = new TournamentMatchParticipantWinnerOfMatch(
			this->winnerOfMatch.matchReference);
		break;
	}
	default: {
		throw  std::runtime_error("unrecognized participant type");
		break;
	}
	}

	return participant;
}

// PlayerComboBox::PlayerComboBox(
// 	std::function<bool(TournamentMatch *)> __matchFilterCallback)
// this->matchFilterCallback = matchFilterCallback;
PlayerComboBox::PlayerComboBox(const TournamentMatch &tournamentMatch)
{
	this->matchFilterCallback = [tournamentMatch](TournamentMatch *match) {
		return match->matchLabel() != tournamentMatch.matchLabel();
	};

	this->setMinimumWidth(200);

	this->setEditable(true);
	auto *comboCompleter = this->completer();
	comboCompleter->setCaseSensitivity(Qt::CaseInsensitive);
	comboCompleter->setFilterMode(Qt::MatchContains);
	comboCompleter->setCompletionMode(QCompleter::PopupCompletion);
}

PlayerComboBox::~PlayerComboBox() {}

void PlayerComboBox::setPlayerOptions(
	const std::vector<PlayerReference> &players,
	const std::vector<MatchReference> matches)
{
	auto textToReset = this->currentText();
	this->clear();
	this->setMaxCount(INT_MAX);

	auto emptyData = new PlayerComboBoxData();
	emptyData->dataType = PlayerComboBoxData::Type::Empty;
	emptyData->empty = {};

	this->addItem("", (long long)emptyData);

	for (unsigned int playerIndex = 0; playerIndex < players.size();
	     playerIndex++) {
		auto playerReference = players[playerIndex];
		auto player = playerReference.player();
		auto staticPlayerData = new PlayerComboBoxData();
		staticPlayerData->dataType =
			PlayerComboBoxData::Type::StaticPlayer;
        staticPlayerData->staticPlayer = { .playerReference = playerReference };
		// staticPlayerData->staticPlayer = {.player = player,
		// 				  .index = playerIndex};
		this->addItem(player->name().c_str(),
			      (long long)staticPlayerData);
	}
	obs_log(LOG_INFO, "[PlayerComboBox::setPlayerOptions] added %d players to player comboboxes",
		players.size());

	auto addedMatchCount = 0;
	for (unsigned int matchIndex = 0; matchIndex < matches.size();
	     matchIndex++) {
	obs_log(LOG_INFO, "[PlayerComboBox::setPlayerOptions] adding winner of match %d",
		matchIndex);
		auto matchReference = matches[matchIndex];
	obs_log(LOG_INFO, "[PlayerComboBox::setPlayerOptions] matchReference matchindex is %d",
		matchReference.matchIndex);
        auto match = matchReference.match();
	obs_log(LOG_INFO, "[PlayerComboBox::setPlayerOptions] match is %p",
		match);

		if (this->matchFilterCallback(match)) {
			const unsigned bufferSize = 64;
			char matchItemText[bufferSize];
			snprintf(matchItemText, bufferSize, "%s %s",
				 obs_module_text("WinnerOfMatch"),
				 match->matchLabel().c_str());

            // MatchReference winnerOfMatchReference(tournamentReference, matchIndex);
            // auto winnerOfMatchReference = matches[];
			auto winnerOfMatchData = new PlayerComboBoxData();
			winnerOfMatchData->dataType =
				PlayerComboBoxData::Type::WinnerOfMatch;
			winnerOfMatchData->winnerOfMatch = {
				.matchReference = matchReference};
			//      {.match = match,
			// .matchIndex =
			//  matchIndex};
			//, .index = matchIndex};
			this->addItem(matchItemText,
				      (long long)winnerOfMatchData);
			addedMatchCount++;
		}
	}

	obs_log(LOG_INFO,
		"[PlayerComboBox::setPlayerOptions] added %d tournament match winners to player comboboxes",
		addedMatchCount);

	auto matchFlags = this->completer()->filterMode();
	auto indexToReset = this->findText(textToReset, matchFlags);
	this->setCurrentIndex(indexToReset);
	this->setMaxCount(1 + (int)players.size() + addedMatchCount);
}

const PlayerComboBoxData *PlayerComboBox::getPlayerData() const
{
	auto playerData = reinterpret_cast<PlayerComboBoxData *>(
		this->currentData().toLongLong());

	if (playerData == nullptr) {
		obs_log(LOG_INFO,
			"[PlayerComboBox::getPlayerData] player data is null");
		playerData = new PlayerComboBoxData();
		playerData->dataType = PlayerComboBoxData::Type::Empty;
		playerData->empty = {};
	}
	return playerData;
}
