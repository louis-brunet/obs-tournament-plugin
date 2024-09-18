#pragma once

#include "src/model/plugin-data-object.hpp"
#include <obs-data.h>
#include <string>

class Tournament;

class TournamentMatchParticipant : public TournamentPluginDataObject {
public:
	enum Type {
		Unknown = 0,
		StaticPlayer,
		WinnerOfMatch,
	};

	// TournamentMatchParticipantBase();
	// TournamentMatchParticipant(Player *player);
	// TournamentMatchParticipant(TournamentMatch *deciderMatch);
	~TournamentMatchParticipant();

	static TournamentMatchParticipant *
	loadStatic(obs_data_t *dataObj);

	TournamentMatchParticipant::Type type();

	virtual bool isValid() const = 0;
	virtual bool isReady() const = 0;
	virtual std::string displayName() const = 0;

	virtual void save(obs_data_t *dataObj) const override;
	virtual void load(obs_data_t *dataObj) override;

protected:
	TournamentMatchParticipant(TournamentMatchParticipant::Type type);
	//,
	// MatchReference matchReference);

	// private:
	TournamentMatchParticipant::Type _type;
	// MatchReference _matchReference;

private:
	static TournamentMatchParticipant::Type loadType(obs_data_t *dataObj);
};
