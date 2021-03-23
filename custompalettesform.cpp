#include "custompalettesform.h"

#include <QDebug>

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

void CustomPalettesForm::newPalette()
{
	Palette newPalette;
	newPalette.setName("Test"+newPalette.getId());
	newPalette.save();
	refreshPalettes();
}

void CustomPalettesForm::delPalette(QString id)
{
	palettes[id]->del();
	refreshPalettes();
}

void CustomPalettesForm::uploadPalette(QString id)
{
	palettes[id]->upload();
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


