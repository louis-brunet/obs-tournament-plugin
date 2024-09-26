#include "tournament-outputs.hpp"
#include "src/data/data-helpers.hpp"
#include "src/logger.hpp"
#include <obs.h>

void TournamentSourceOutput::load(obs_data_t *data)
{
    this->sourceUuid = ObsDataHelpers::getString(data, "sourceUuid", "");
}

void TournamentSourceOutput::save(obs_data_t *data) const
{
    obs_data_set_string(data, "sourceUuid", this->sourceUuid.c_str());
}

TournamentOutputs::TournamentOutputs() {}
TournamentOutputs::~TournamentOutputs() {}

void TournamentOutputs::load(obs_data_t *data)
{
    if (!data) {
        return;
    }

    OBSDataAutoRelease currentMatchData =
        obs_data_get_obj(data, "currentMatch");
    this->currentMatch.load(currentMatchData);

    OBSDataAutoRelease upcomingMatchData =
        obs_data_get_obj(data, "upcomingMatch");
    this->upcomingMatch.load(upcomingMatchData);

    OBSDataAutoRelease participant1NameData =
        obs_data_get_obj(data, "participant1Name");
    this->participant1Name.load(participant1NameData);

    OBSDataAutoRelease participant2NameData =
        obs_data_get_obj(data, "participant2Name");
    this->participant2Name.load(participant2NameData);

    OBSDataAutoRelease participant1ScoreData =
        obs_data_get_obj(data, "participant1Score");
    this->participant1Score.load(participant1ScoreData);

    OBSDataAutoRelease participant2ScoreData =
        obs_data_get_obj(data, "participant2Score");
    this->participant2Score.load(participant2ScoreData);

    OBSDataAutoRelease participant1ImageData =
        obs_data_get_obj(data, "participant1Image");
    this->participant1Image.load(participant1ImageData);

    OBSDataAutoRelease participant2ImageData =
        obs_data_get_obj(data, "participant2Image");
    this->participant2Image.load(participant2ImageData);

    OBSDataAutoRelease participant1DescriptionData =
        obs_data_get_obj(data, "participant1Description");
    this->participant1Description.load(participant1DescriptionData);

    OBSDataAutoRelease participant2DescriptionData =
        obs_data_get_obj(data, "participant2Description");
    this->participant2Description.load(participant2DescriptionData);
}

void TournamentOutputs::save(obs_data_t *data) const
{

    OBSDataAutoRelease currentMatchData = obs_data_create();
    this->currentMatch.save(currentMatchData);
    obs_data_set_obj(data, "currentMatch", currentMatchData);

    OBSDataAutoRelease upcomingMatchData = obs_data_create();
    this->upcomingMatch.save(upcomingMatchData);
    obs_data_set_obj(data, "upcomingMatch", upcomingMatchData);

    OBSDataAutoRelease participant1NameData = obs_data_create();
    this->participant1Name.save(participant1NameData);
    obs_data_set_obj(data, "participant1Name", participant1NameData);

    OBSDataAutoRelease participant2NameData = obs_data_create();
    this->participant2Name.save(participant2NameData);
    obs_data_set_obj(data, "participant2Name", participant2NameData);

    OBSDataAutoRelease participant1ScoreData = obs_data_create();
    this->participant1Score.save(participant1ScoreData);
    obs_data_set_obj(data, "participant1Score", participant1ScoreData);

    OBSDataAutoRelease participant2ScoreData = obs_data_create();
    this->participant2Score.save(participant2ScoreData);
    obs_data_set_obj(data, "participant2Score", participant2ScoreData);

    OBSDataAutoRelease participant1ImageData = obs_data_create();
    this->participant1Image.save(participant1ImageData);
    obs_data_set_obj(data, "participant1Image", participant1ImageData);

    OBSDataAutoRelease participant2ImageData = obs_data_create();
    this->participant2Image.save(participant2ImageData);
    obs_data_set_obj(data, "participant2Image", participant2ImageData);

    OBSDataAutoRelease participant1DescriptionData = obs_data_create();
    this->participant1Description.save(participant1DescriptionData);
    obs_data_set_obj(data, "participant1Description",
                     participant1DescriptionData);

    OBSDataAutoRelease participant2DescriptionData = obs_data_create();
    this->participant2Description.save(participant2DescriptionData);
    obs_data_set_obj(data, "participant2Description",
                     participant2DescriptionData);
}

void TournamentSourceOutput::setSourceText(const char *text)
{
    this->setSourceSettingString("text", text);
}

void TournamentSourceOutput::setSourceImageFile(const char *imageFilePath)
{
    this->setSourceSettingString("file", imageFilePath);
}

void TournamentSourceOutput::setSourceSettingString(const char *settingName,
                                                    const char *settingValue)
{
    if (this->sourceUuid == "") {
        return;
    }

    OBSSourceAutoRelease source =
        obs_get_source_by_uuid(this->sourceUuid.c_str());
    if (!source) {
        return;
    }

    OBSDataAutoRelease sourceSettings = obs_source_get_settings(source);
    if (!sourceSettings) {
        return;
    }

    obs_data_set_string(sourceSettings, settingName, settingValue);
    obs_source_update(source, sourceSettings);
}
