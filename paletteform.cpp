#include "paletteform.h"
#include "devicemanager.h"

PaletteForm::PaletteForm(QObject *parent)
{

}

void PaletteForm::ApplyChanges()
{
	qDebug() << "Apply";
	DeviceManager* dm = DeviceManager::getInstance();
	dm->QueryWrite("B"+brightness);
	dm->QueryWrite("p"+palette+(linearBlending ? "l" : "n"));
	dm->QueryWrite("d"+delay);
}

void PaletteForm::setPalette(QString palette)
{
	qDebug() << "Palette:" << palette;
	this->palette = sigmonPalette[palette];
}

void PaletteForm::setLinearBlending(bool linearBlending)
{
	qDebug() << "Blending:" << linearBlending;
	this->linearBlending = linearBlending;
}

void PaletteForm::setDelay(int delay)
{
	qDebug() << "Delay:" << delay;
	this->delay = DeviceManager::getInstance()->ConvertNumToWritable(delay, true);
}

void PaletteForm::setBrightness(int brightness)
{
	qDebug() << "Brightness:" << brightness;
	this->brightness = DeviceManager::getInstance()->ConvertNumToWritable(brightness);
}
