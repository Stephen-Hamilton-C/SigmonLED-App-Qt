#include "palette.h"
#include "devicemanager.h"

#include <QUuid>
#include <QDebug>

QVariantList Palette::defaultColors = QVariantList() << QColor(255, 0, 0) << QColor(127, 127, 127) << QColor(0, 0, 255) << QColor(0, 0, 0)
													 << QColor(255, 0, 0) << QColor(127, 127, 127) << QColor(0, 0, 255) << QColor(0, 0, 0)
													 << QColor(255, 0, 0) << QColor(255, 0, 0) << QColor(127, 127, 127) << QColor(127, 127, 127)
													 << QColor(0, 0, 255) << QColor(0, 0, 255) << QColor(0, 0, 0) << QColor(0, 0, 0);

Palette::Palette(QObject *parent) : QObject(parent)
{
	id = QUuid::createUuid().toString();
	colors = Palette::defaultColors;
}

Palette::Palette(QString id, QObject *parent) : QObject(parent)
{
	this->id = id;
	load(id);
}

void Palette::upload()
{
	QString writeString = "C";
	for(int i = 0; i < colors.count(); i++){
		ColorRGB color = ColorRGB::fromHEX(colors.at(i).toString());

		writeString += "r";
		writeString += DeviceManager::ConvertNumToWritable(color.r);
		writeString += "g";
		writeString += DeviceManager::ConvertNumToWritable(color.g);
		writeString += "b";
		writeString += DeviceManager::ConvertNumToWritable(color.b);
		writeString += "#";

	}

	DeviceManager::getInstance()->QueueWrite(writeString);
}

QString Palette::toString()
{
	QString colorsString;
	for(int i = 0; i < colors.count(); i++){
		colorsString += colors[i].toString()+", ";
	}

	return id+", "+name+", "+colorsString;
}

bool Palette::compare(Palette const &otherPalette) const
{
	return (otherPalette.getName() == name && otherPalette.getColors() == colors && otherPalette.getId() == id);
}

void Palette::save()
{
	QStringList palettes = settings.value("CustomPalettes").toStringList();
	if(!palettes.contains(id)){
		palettes.append(id);
	}

	settings.setValue("CustomPalettes/"+id+"/name", name);
	settings.setValue("CustomPalettes/"+id+"/colors", colors);
	settings.setValue("CustomPalettes", palettes);
}

void Palette::load(QString id)
{
	name = settings.value("CustomPalettes/"+id+"/name", "New Palette").toString();
	colors = settings.value("CustomPalettes/"+id+"/colors", Palette::defaultColors).toList();
}

void Palette::del()
{
	qDebug() << "Deleting" << id;
	QStringList palettes = settings.value("CustomPalettes").toStringList();
	if(palettes.contains(id)){
		qDebug() << "Success";
		palettes.removeAll(id);
	}

	settings.remove("CustomPalettes/"+id+"/name");
	settings.remove("CustomPalettes/"+id+"/colors");
	settings.setValue("CustomPalettes", palettes);

	delete this;
}


