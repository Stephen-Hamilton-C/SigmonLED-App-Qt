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

    hue = settings.value("HSVHue"+settingName, 0).toInt();
    saturation = settings.value("HSVSaturation"+settingName, 0).toInt();
    value = settings.value("HSVValue"+settingName, 0).toInt();
    QTimer::singleShot(100, this, [this]{
        emit hueChanged(hue);
        emit saturationChanged(saturation);
        emit brightnessChanged(value);
    });
}

void ColorPicker::saveSettings()
{
    settings.setValue("HSVHue"+settingName, hue);
    settings.setValue("HSVSaturation"+settingName, saturation);
    settings.setValue("HSVValue"+settingName, value);
}
