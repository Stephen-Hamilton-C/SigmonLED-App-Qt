#include "palettecolormodel.h"

PaletteColorModel::PaletteColorModel(QString labelText, QColor color, QObject *parent) : QObject(parent)
{
	this->labelText = labelText;
	this->color = color;
}
