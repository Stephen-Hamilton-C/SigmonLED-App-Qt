#include "paletteform.h"
#include "devicemanager.h"

PaletteForm::PaletteForm(QObject *parent)
{
	linearBlending = settings.value("LinearBlending", true).toBool();
	solidPalette = settings.value("SolidPalette", false).toBool();
	brightness = settings.value("Brightness", "255").toString();
	delay = settings.value("Delay", "0010").toString();
	palette = sigmonPalette[settings.value("Palette", "r").toString()];

	QTimer::singleShot(100, this, [this]{
		emit linearBlendingChanged(linearBlending);
		emit solidPaletteChanged(solidPalette);
		emit brightnessChanged(brightness.toInt());
		emit delayChanged(delay.toInt());
		emit paletteChanged(palette);
	});
}

PaletteForm::~PaletteForm()
{
	settings.setValue("LinearBlending", linearBlending);
	settings.setValue("SolidPalette", solidPalette);
	settings.setValue("Brightness", brightness);
	settings.setValue("Delay", delay);
	settings.setValue("Palette", palette);
}

void PaletteForm::ApplyChanges()
{
	qDebug() << "Apply";
	DeviceManager* dm = DeviceManager::getInstance();

	//Set the brightness
	dm->QueueWrite("B"+brightness);

	//Sanity check on palette
	if(palette.isEmpty())
		palette = "r";

	//Let's walk through this mess.
	//First line is solid palette (P) or standard running palette (p).
	//Next line is the palette selected, converted into the Arduino char.
	//Last line is the linear blending toggle. l for blending, n for none.
	dm->QueueWrite((solidPalette ? "P" : "p")
				   + palette +
				   (linearBlending ? "l" : "n"));

	//Set time between color updates
	dm->QueueWrite("d"+delay);
}

void PaletteForm::setPalette(QString palette)
{
	qDebug() << "Palette:" << palette;
	this->palette = sigmonPalette[palette];
	settings.setValue("Palette", palette);
}

void PaletteForm::setLinearBlending(bool linearBlending)
{
	qDebug() << "Blending:" << linearBlending;
	this->linearBlending = linearBlending;
}

void PaletteForm::setSolidPalette(bool solidPalette)
{
	qDebug() << "Solid Palette:" << solidPalette;
	this->solidPalette = solidPalette;
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

void PaletteForm::testCustomPalette()
{
	//Cr255g000b000#r127g127b127#r000g000b255#r000g000b000#r255g000b000#r127g127b127#r000g000b255#r000g000b000#r255g000b000#r255g000b000#r127g127b127#r127g127b127#r000g000b255#r000g000b255#r000g000b000#r000g000b000##
	DeviceManager::getInstance()->QueueWrite(
				"C"
				"r255g000b000#"
				"r127g127b127#"
				"r000g000b255#"
				"r000g000b000#"
				"r255g000b000#"
				"r127g127b127#"
				"r000g000b255#"
				"r000g000b000#"
				"r255g000b000#"
				"r255g000b000#"
				"r127g127b127#"
				"r127g127b127#"
				"r000g000b255#"
				"r000g000b255#"
				"r000g000b000#"
				"r000g000b000#"
				"#"
	);
}
