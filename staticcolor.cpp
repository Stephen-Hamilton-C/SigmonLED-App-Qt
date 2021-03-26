#include "staticcolor.h"
#include "colorrgb.h"
#include "devicemanager.h"

#include <QDebug>

StaticColor::StaticColor(QObject *parent) : QObject(parent)
{

}

void StaticColor::apply(double h, double s, double v)
{
	qDebug() << "Apply";

	//Convert from HSV to RGB. See header def for HSVtoRGB for argument ranges.
	ColorRGB color = ColorRGB::fromHSV(h, s/255.0, v/255.0);

	DeviceManager* dm = DeviceManager::getInstance();
	//Set full brightness as this will effectively be controlled by HSV
	dm->QueueWrite("xBFF");

	//Set RGB
	dm->QueueWrite("r"+dm->ConvertNumToWritable(color.r));
	dm->QueueWrite("g"+dm->ConvertNumToWritable(color.g));
	dm->QueueWrite("b"+dm->ConvertNumToWritable(color.b));
}
