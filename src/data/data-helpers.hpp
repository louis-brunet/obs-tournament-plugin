#pragma once

#include <functional>
#include <obs-data.h>
#include <obs.hpp>
#include <vector>

namespace ObsDataHelpers {
const char *getString(obs_data_t *data, const char *name,
		      const char *defaultString = "[???]");

long long getInt(obs_data_t *data, const char *name, long long defaultInt);
bool getBool(obs_data_t *data, const char *name, bool defaultValue);

void iterateArray(
	obs_data_t *data, const char *arrayName,
	std::function<void(obs_data_t *, unsigned long)> iterateCallback);

template<typename Enum>
Enum getEnum(obs_data_t *data, const char *name, long long defaultValue)
{
    return static_cast<Enum>(
        ObsDataHelpers::getInt(data, name, defaultValue));
}

template<typename Saveable>
void saveArray(
	obs_data_t *data, const char *arrayName,
	const std::vector<Saveable> &items,
	std::function<void(const Saveable &, obs_data_t *data)> saveCallback)
{
	OBSDataArrayAutoRelease dataArray = obs_data_array_create();
	for (auto item : items) {
		OBSDataAutoRelease itemDataObj = obs_data_create();
        saveCallback(item, itemDataObj);
		obs_data_array_push_back(dataArray, itemDataObj);
	}
	obs_data_set_array(data, arrayName, dataArray);
}
} // namespace ObsDataHelpers
