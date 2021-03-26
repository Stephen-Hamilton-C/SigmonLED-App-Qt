#include "custompalettesform.h"
#include "devicemanager.h"

#include <QDebug>

QMap<QString, Palette*> CustomPalettesForm::palettes;

CustomPalettesForm::CustomPalettesForm(QObject *parent) : QObject(parent)
{
	list = new PaletteList();
	refreshPalettes();
}

void CustomPalettesForm::refreshPalettes()
{
	palettes.clear();
	QVector<PaletteItem> items;

	QStringList storedPalettes = settings.value("CustomPalettes").toStringList();
	for(int i = 0; i < storedPalettes.count(); i++){
		Palette* palette = new Palette(storedPalettes.at(i));
		palettes.insert(palette->getId(), palette);
		items.append({ palette->getName(), palette->getId(), palette->getColors() });
		qDebug() << "Found palette:" << palette->toString();
	}

	list->setItems(items);
	emit listChanged();

	qDebug() << "StoredPalettes:" << storedPalettes;
}

QString CustomPalettesForm::newPalette()
{
	Palette palette;
	palette.setName("New Palette");
	palette.save();
	refreshPalettes();

	return palette.getId();
}

void CustomPalettesForm::delPalette(QString id)
{
	palettes[id]->del();
	refreshPalettes();
}

void CustomPalettesForm::uploadPalette(QString id)
{
	startingLength = palettes[id]->upload();
	activateProgress = true;
	connect(DeviceManager::getInstance(), &DeviceManager::writeBufferChanged, this, &CustomPalettesForm::writeBufferUpdated);
}

void CustomPalettesForm::writeBufferUpdated(QString writeBuffer)
{
	sendingPalette = activateProgress && writeBuffer.length() > 0;
	sendingProgress = (double)writeBuffer.length() / (double)startingLength;
	emit sendingPaletteChanged(sendingPalette);
	emit sendingProgressChanged(sendingProgress);
	qDebug() << "sendingPalette:" << sendingPalette;

	if(writeBuffer.length() == 0){
		activateProgress = false;
		disconnect(DeviceManager::getInstance(), &DeviceManager::writeBufferChanged, this, &CustomPalettesForm::writeBufferUpdated);
	}
}

double CustomPalettesForm::getSendingProgress() const
{
	return sendingProgress;
}

void CustomPalettesForm::setSendingProgress(double value)
{
	sendingProgress = value;
}

bool CustomPalettesForm::getSendingPalette() const
{
	return sendingPalette;
}

void CustomPalettesForm::setSendingPalette(bool value)
{
	sendingPalette = value;
}

PaletteList *CustomPalettesForm::getList() const
{
	return list;
}

void CustomPalettesForm::setList(PaletteList *value)
{
	list = value;
}


