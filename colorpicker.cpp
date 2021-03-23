#include "colorpicker.h"
#include "devicemanager.h"
#include "colorrgb.h"

ColorPicker::ColorPicker(QObject *parent) : QObject(parent)
{

}

ColorPicker::~ColorPicker()
{
    saveSettings();
}

void ColorPicker::setSettingName(QString name)
{
    settingName = name;

	hue = settings.value(settingName+"HSVHue", 0).toInt();
	saturation = settings.value(settingName+"HSVSaturation", 0).toInt();
	value = settings.value(settingName+"HSVValue", 0).toInt();
    QTimer::singleShot(100, this, [this]{
        emit hueChanged(hue);
        emit saturationChanged(saturation);
        emit brightnessChanged(value);
    });
}

void ColorPicker::saveSettings()
{
	settings.setValue(settingName+"HSVHue", hue);
	settings.setValue(settingName+"HSVSaturation", saturation);
	settings.setValue(settingName+"HSVValue", value);
}
