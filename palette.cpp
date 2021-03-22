#include "palette.h"

#include <QUuid>

QVariantList Palette::defaultColors = QVariantList() << QColor(255, 0, 0) << QColor(127, 127, 127) << QColor(0, 0, 255) << QColor(0, 0, 0)
													 << QColor(255, 0, 0) << QColor(127, 127, 127) << QColor(0, 0, 255) << QColor(0, 0, 0)
													 << QColor(255, 0, 0) << QColor(255, 0, 0) << QColor(127, 127, 127) << QColor(127, 127, 127)
													 << QColor(0, 0, 255) << QColor(0, 0, 255) << QColor(0, 0, 0) << QColor(0, 0, 0);

Palette::Palette(QObject *parent) : QObject(parent)
{
	id = QUuid::createUuid().toString();
	colors = Palette::defaultColors;
}

void Palette::save()
{
	QStringList palettes = settings.value("CustomPalettes").toStringList();
	if(!palettes.contains(id)){
		palettes.append(id);
	}

	settings.setValue(id+"name", name);
	settings.setValue(id+"colors", colors);
}

void Palette::load(QString id)
{
	name = settings.value(id+"name", "New Palette").toString();
	colors = settings.value(id+"colors", Palette::defaultColors).toList();
}

void Palette::del()
{
	QStringList palettes = settings.value("CustomPalettes").toStringList();
	if(palettes.contains(id)){
		palettes.removeAll(id);
	}

	delete this;
}


