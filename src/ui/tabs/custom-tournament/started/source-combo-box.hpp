#pragma once
#include "src/ui/components/labeled-input.hpp"
#include <QComboBox>

class SourceComboBox : public AppLabeledInput {
    Q_OBJECT;

public:
    enum Type {
        TextSource,
        ImageSource,
    };

    SourceComboBox(const char *labelText, Type sourceType);
    ~SourceComboBox();

    void setCurrentSource(const char *sourceUuid);

signals:
    void sourceChanged(std::string newUuid);

private:
    QComboBox *_comboBox;
};
