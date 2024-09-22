#pragma once

#include <obs-data.h>
#include <obs.hpp>

class TournamentPluginDataObject {
public:
	// // template<class ObjectType>
	// // static void loadArray(
	// // 	obs_data_t *dataObj, const char *name,
	// // 	std::vector<ObjectType *> &outputVector,
	// // 	std::function<ObjectType *(obs_data_t *)> createCallback,
	// // 	std::vector<obs_data_t *> defaultDataItems = {});
	// // template<class ObjectType>
	// // static void
	// // saveArray(obs_data_t *dataObj, const char *name,
	// // 	  const std::vector<ObjectType *> &dataItems);
	//
	// template<class ObjectType>
	// static void
	// loadArray(obs_data_t *dataObj, const char *name,
	// 	  std::vector<ObjectType *> &outputVector,
	// 	  std::function<ObjectType *(obs_data_t *)> createCallback,
	// 	  std::vector<obs_data_t *> defaultDataItems = {})
	// {
	// 	OBSDataArrayAutoRelease defaultDataArray =
	// 		obs_data_array_create();
	// 	for (unsigned int index = 0; index < defaultDataItems.size();
	// 	     index++) {
	// 		obs_data_array_insert(defaultDataArray, index,
	// 				      defaultDataItems.at(index));
	// 	}
	// 	obs_data_set_default_array(dataObj, name, defaultDataArray);
	// 	OBSDataArrayAutoRelease dataArray =
	// 		obs_data_get_array(dataObj, name);
	//
	// 	// auto outputVector = new std::vector<ObjectType *>;
	// 	for (unsigned int index = 0;
	// 	     index < obs_data_array_count(dataArray); index++) {
	// 		const OBSDataAutoRelease itemDataObj =
	// 			obs_data_array_item(dataArray, index);
	// 		auto newObject = createCallback(itemDataObj);
	// 		outputVector.push_back(newObject);
	// 	}
	// }
	//
	// template<class ObjectType>
	// static void saveArray(obs_data_t *dataObj, const char *name,
	// 		      const std::vector<ObjectType *> &dataItems)
	// {
	// 	OBSDataArrayAutoRelease dataArray = obs_data_array_create();
	// 	for (TournamentPluginDataObject *item : dataItems) {
	// 		OBSDataAutoRelease itemDataObj = obs_data_create();
	// 		item->save(itemDataObj);
	// 		obs_data_array_push_back(dataArray, itemDataObj);
	// 	}
	// 	obs_data_set_array(dataObj, name, dataArray);
	// }
    virtual ~TournamentPluginDataObject();

	virtual void save(obs_data_t *dataObj) const = 0;
	virtual void load(obs_data_t *dataObj) = 0;

protected:
    TournamentPluginDataObject() = default;
    TournamentPluginDataObject(TournamentPluginDataObject &&) = default;
    TournamentPluginDataObject(const TournamentPluginDataObject &) = default;
    TournamentPluginDataObject &operator=(TournamentPluginDataObject &&) = default;
    TournamentPluginDataObject &operator=(const TournamentPluginDataObject &) = default;
};

