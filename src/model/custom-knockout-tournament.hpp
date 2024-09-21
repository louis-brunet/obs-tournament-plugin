#pragma once

#include "src/model/tournament-reference.hpp"
#include "src/model/tournament.hpp"
#include <obs-module.h>

class CustomKnockoutTournament : public Tournament {
public:
	// static CustomKnockoutTournament *loadStatic(obs_data_t *dataObj);

	CustomKnockoutTournament(
		TournamentReference reference,
		std::vector<Player *> &&players = {},
		std::string title = obs_module_text("CustomKnockoutTabTitle"));
	// CustomKnockoutTournament(const std::vector<Player *> &players = {});
	CustomKnockoutTournament(CustomKnockoutTournament &&) = default;
	CustomKnockoutTournament(const CustomKnockoutTournament &) = default;
	CustomKnockoutTournament &
	operator=(CustomKnockoutTournament &&) = default;
	CustomKnockoutTournament &
	operator=(const CustomKnockoutTournament &) = default;
	~CustomKnockoutTournament();

	void save(obs_data_t *) const override;
	void load(obs_data_t *) override;

	// std::vector<TournamentMatch *> &matches();
	// std::vector<TournamentMatch *> matches;
	bool isStarted() const;
	void start();

private:
	bool _isStarted;
};
