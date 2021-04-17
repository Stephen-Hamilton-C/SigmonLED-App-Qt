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

void ColorPicker::setSettingName(QString prefix)
{
    settingPrefix = prefix;

    hue = settings.value(settingPrefix+"HSVHue", 0).toInt();
    saturation = settings.value(settingPrefix+"HSVSaturation", 0).toInt();
    value = settings.value(settingPrefix+"HSVValue", 0).toInt();
    QTimer::singleShot(100, this, [this]{
        emit hueChanged(hue);
        emit saturationChanged(saturation);
        emit brightnessChanged(value);
    });
}

void ColorPicker::saveSettings()
{
    settings.setValue(settingPrefix+"HSVHue", hue);
    settings.setValue(settingPrefix+"HSVSaturation", saturation);
    settings.setValue(settingPrefix+"HSVValue", value);
}
