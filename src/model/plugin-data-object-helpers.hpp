#pragma once

#include "src/model/plugin-data-object.hpp"
#include <functional>
#include <obs-data.h>
#include <obs.hpp>
#include <vector>

class TournamentPluginDataObjectHelpers {
public:
	// template<class ObjectType>
	// static void loadArray(
	// 	obs_data_t *dataObj, const char *name,
	// 	std::vector<ObjectType *> &outputVector,
	// 	std::function<ObjectType *(obs_data_t *)> createCallback,
	// 	std::vector<obs_data_t *> defaultDataItems = {});
	// template<class ObjectType>
	// static void
	// saveArray(obs_data_t *dataObj, const char *name,
	// 	  const std::vector<ObjectType *> &dataItems);
	static void
	iterateArray(obs_data_t *dataObj, const char *name,
		     std::function<void(obs_data_t *itemDataObj,
					unsigned long itemIndex)>
			     iterateCallback,
		     std::vector<obs_data_t *> defaultDataItems = {})
	{
		OBSDataArrayAutoRelease defaultDataArray =
			obs_data_array_create();
		for (unsigned int index = 0; index < defaultDataItems.size();
		     index++) {
			obs_data_array_insert(defaultDataArray, index,
					      defaultDataItems.at(index));
		}
		obs_data_set_default_array(dataObj, name, defaultDataArray);
		OBSDataArrayAutoRelease dataArray =
			obs_data_get_array(dataObj, name);

		for (unsigned int index = 0;
		     index < obs_data_array_count(dataArray); index++) {
			const OBSDataAutoRelease itemDataObj =
				obs_data_array_item(dataArray, index);
			iterateCallback(itemDataObj);
		}
	}

	template<class ObjectType>
	static void
	loadArray(obs_data_t *dataObj, const char *name,
		  std::vector<ObjectType *> &outputVector,
		  std::function<ObjectType *(obs_data_t *)> createCallback,
		  // std::function<void(obs_data_t *)> loadCallback,
		  std::vector<obs_data_t *> defaultDataItems = {})
	{
		OBSDataArrayAutoRelease defaultDataArray =
			obs_data_array_create();
		for (unsigned int index = 0; index < defaultDataItems.size();
		     index++) {
			obs_data_array_insert(defaultDataArray, index,
					      defaultDataItems.at(index));
		}
		obs_data_set_default_array(dataObj, name, defaultDataArray);
		OBSDataArrayAutoRelease dataArray =
			obs_data_get_array(dataObj, name);

		// auto outputVector = new std::vector<ObjectType *>;
		for (unsigned int index = 0;
		     index < obs_data_array_count(dataArray); index++) {
			const OBSDataAutoRelease itemDataObj =
				obs_data_array_item(dataArray, index);
			auto newObject = createCallback(itemDataObj);
			outputVector.push_back(newObject);
		}
	}

	template<class ObjectType>
	static void saveArray(obs_data_t *dataObj, const char *name,
			      const std::vector<ObjectType *> &dataItems)
	{
		OBSDataArrayAutoRelease dataArray = obs_data_array_create();
		for (TournamentPluginDataObject *item : dataItems) {
			OBSDataAutoRelease itemDataObj = obs_data_create();
			item->save(itemDataObj);
			obs_data_array_push_back(dataArray, itemDataObj);
		}
		obs_data_set_array(dataObj, name, dataArray);
	}
};
