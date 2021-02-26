#include "colorpicker.h"
#include "devicemanager.h"
#include "ColorRGB.h"

ColorPicker::ColorPicker(QObject *parent) : QObject(parent)
{
	//TODO: Make this start from QML rather than construct. Let QML define which settings to load
	h = settings.value("HSVHue", 0).toInt();
	s = settings.value("HSVSaturation", 0).toInt();
	v = settings.value("HSVValue", 0).toInt();
	QTimer::singleShot(100, this, [this]{
		emit hueChanged(h);
		emit saturationChanged(s);
		emit brightnessChanged(v);
	});
}

ColorPicker::~ColorPicker()
{
	settings.setValue("HSVHue", h);
	settings.setValue("HSVSaturation", s);
	settings.setValue("HSVValue", v);
}

void ColorPicker::setH(int h)
{
	qDebug() << "Hue:" << h;
	this->h = h;
}

void ColorPicker::setS(int s)
{
	qDebug() << "Saturation:" << s;
	this->s = s;
}

void ColorPicker::setV(int v)
{
	qDebug() << "Value:" << v;
	this->v = v;
}
