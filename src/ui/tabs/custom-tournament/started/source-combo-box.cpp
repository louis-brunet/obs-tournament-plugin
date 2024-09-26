#include "source-combo-box.hpp"
#include "src/data/plugin-data.hpp"
#include <QComboBox>
#include <obs.hpp>
#include <util/c99defs.h>

SourceComboBox::SourceComboBox(const char *labelText, Type sourceType)
    : AppLabeledInput(labelText, new QComboBox(),
                      AppLabeledInput::LabelPosition::Left)
{
    std::vector<OBSWeakSource> weakSources;

    switch (sourceType) {
    case TextSource:
        weakSources = pluginData->textSources();
        break;
    case ImageSource:
        weakSources = pluginData->imageSources();
        break;
    }

    this->_comboBox = reinterpret_cast<QComboBox *>(this->_inputWidget);

    this->_comboBox->addItem("", QString(""));
    for (auto weakSource : weakSources) {
        OBSSourceAutoRelease source = obs_weak_source_get_source(weakSource);
        auto sourceName = obs_source_get_name(source);
        QString sourceUuid = obs_source_get_uuid(source);
        this->_comboBox->addItem(sourceName, sourceUuid);
    }

    this->connect(this->_comboBox, &QComboBox::currentIndexChanged, [this]() {
        std::string newUuid =
            this->_comboBox->currentData().toString().toStdString();
        this->sourceChanged(newUuid);
    });
}

SourceComboBox::~SourceComboBox() {}

void SourceComboBox::setCurrentSource(const char *newUuid)
{
    auto foundIndex = this->_comboBox->findData(QString(newUuid));
    this->_comboBox->setCurrentIndex(foundIndex);
}
