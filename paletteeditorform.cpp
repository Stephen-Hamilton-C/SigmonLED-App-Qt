#include "paletteeditorform.h"
#include "custompalettesform.h"

PaletteEditorForm::PaletteEditorForm(QObject *parent) : QObject(parent), currentPalette(nullptr)
{
	list = new PaletteEditorList();
}

PaletteEditorList *PaletteEditorForm::getList() const
{
	return list;
}

void PaletteEditorForm::setList(PaletteEditorList *value)
{
	list = value;
}

QString PaletteEditorForm::getPaletteID() const
{
	return paletteID;
}

void PaletteEditorForm::setPaletteID(const QString &value)
{
	paletteID = value;
	emit paletteIDChanged(value);

	currentPalette = CustomPalettesForm::palettes[paletteID];
	QVector<PaletteEditorItem> items;

	for(int i = 0; i < currentPalette->getColors().length(); i++){
		items.append(PaletteEditorItem(QString::number(i+1), currentPalette->getColors().at(i).toString()));
	}

	list->setItems(items);
	emit listChanged(list);

	emit nameChanged(getName());
}

QString PaletteEditorForm::getName() const
{
	if(!currentPalette)
		return "";

	return currentPalette->getName();
}

void PaletteEditorForm::setName(const QString &value)
{
	if(!currentPalette)
		return;

	currentPalette->setName(value);
	emit nameChanged(value);
}

void PaletteEditorForm::savePalette()
{
	if(!currentPalette)
		return;

	currentPalette->save();
}
