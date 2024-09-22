#include "data-helpers.hpp"
#include <obs.hpp>

namespace ObsDataHelpers {
const char *getString(obs_data_t *data, const char *name,
		      const char *defaultString)
{
	if (!data) {
		return defaultString;
	}

	obs_data_set_default_string(data, name, defaultString);
	return obs_data_get_string(data, name);
}

long long getInt(obs_data_t *data, const char *name, long long defaultInt)
{
	if (!data) {
		return defaultInt;
	}

	obs_data_set_default_int(data, name, defaultInt);
	return obs_data_get_int(data, name);
}

void iterateArray(
	obs_data_t *data, const char *arrayName,
	std::function<void(obs_data_t *, unsigned long)> iterateCallback)
{
	OBSDataArrayAutoRelease dataArray = obs_data_get_array(data, arrayName);
	if (dataArray) {
		for (unsigned long index = 0;
		     index < obs_data_array_count(dataArray); index++) {
			OBSDataAutoRelease itemData =
				obs_data_array_item(dataArray, index);

			iterateCallback(itemData, index);
		}
	}
}
} // namespace ObsDataHelpers
