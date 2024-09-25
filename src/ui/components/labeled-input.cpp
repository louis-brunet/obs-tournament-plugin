#include "labeled-input.hpp"
#include "src/ui/components/label.hpp"
#include <QBoxLayout>

AppLabeledInput::AppLabeledInput(const std::string &labelText,
				 QWidget *inputWidget,
				 LabelPosition labelPosition): _inputWidget(inputWidget)
{
	auto label = new AppLabel(labelText.c_str());

	QBoxLayout *widgetLayout;
	switch (labelPosition) {
	case Left:
		widgetLayout = new QHBoxLayout();
		widgetLayout->setAlignment(Qt::AlignLeft);
		break;
	case Top:
		widgetLayout = new QVBoxLayout();
		widgetLayout->setAlignment(Qt::AlignTop);
		break;
	default:
		throw std::runtime_error(
			"[AppLabeledInput] unrecognized label position");
	}
	widgetLayout->addWidget(label, 0);
	widgetLayout->addWidget(this->_inputWidget, 0);
	this->setLayout(widgetLayout);

	this->connect(label, &AppLabel::clicked, [inputWidget]() {
		inputWidget->setFocus(Qt::FocusReason::MouseFocusReason);
	});
}

AppLabeledInput::~AppLabeledInput() {}
