#pragma once

#include "src/model/match-reference.hpp"
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

	struct ValidateResult {
        struct InvalidData {
				std::string message = "";
			};
        struct ValidData {
			};

		enum Type {
			Valid,
			Invalid,
		} type =
			TournamentMatchParticipant::ValidateResult::Type::Invalid;



		union Data {
			InvalidData invalid = {};
			ValidData valid;

            // Data(Data &other) = default;
            Data(InvalidData data): invalid(data) {}
            Data(ValidData data): valid(data) {}
            ~Data();
            // Data(Data &other) = default;
		} data;

        ValidateResult(InvalidData _data): type(Type::Invalid), data(_data) {}
        ValidateResult(ValidData _data): type(Type::Valid), data(_data) {}
        // ValidateResult(ValidateResult::Type type, ValidateResult::Data data);
		// ValidateResult(ValidateResult::Type type =
		// 		       TournamentMatchParticipant::
		// 			       ValidateResult::Type::Invalid);
		~ValidateResult() = default;

		bool isValid();
	};

	// TournamentMatchParticipantBase();
	// TournamentMatchParticipant(Player *player);
	// TournamentMatchParticipant(TournamentMatch *deciderMatch);
	~TournamentMatchParticipant();

	static TournamentMatchParticipant *loadStatic(obs_data_t *dataObj);

	TournamentMatchParticipant::Type type();

	virtual TournamentMatchParticipant::ValidateResult validate(MatchReference &matchReference) const = 0;
	// virtual bool isValid() const = 0;
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
