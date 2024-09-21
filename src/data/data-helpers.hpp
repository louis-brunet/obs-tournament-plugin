#pragma once

#include <functional>
#include <obs-data.h>

namespace ObsDataHelpers {
const char *getString(obs_data_t *data, const char *name,
		       const char *defaultString = "[???]");

long long getInt(obs_data_t *data, const char *name, long long defaultInt);

template<typename Enum>
Enum getEnum(obs_data_t *data, const char *name, long long defaultValue);

void iterateArray(
	obs_data_t *data, const char *arrayName,
	std::function<void(obs_data_t *, unsigned long)> iterateCallback);
} // namespace ObsDataHelpers
