#include "paletteform.h"
#include "devicemanager.h"

PaletteForm::PaletteForm(QObject *parent)
{
	linearBlending = settings.value("LinearBlending", true).toBool();
	solidPalette = settings.value("SolidPalette", false).toBool();
	brightness = settings.value("Brightness", 255).toInt();
	delay = settings.value("Delay", 10).toInt();

	//Don't change palette until this is fixed (check TODO in changelog)
	//palette = sigmonPalette[settings.value("Palette", "r").toString()];

	QTimer::singleShot(100, this, [this]{
		emit linearBlendingChanged(linearBlending);
		emit solidPaletteChanged(solidPalette);
		emit brightnessChanged(brightness);
		emit delayChanged(delay);
		//emit paletteChanged(palette);
	});

	dm = DeviceManager::getInstance();
}

void PaletteForm::ApplyChanges()
{
	qDebug() << "Apply";

	dm->QueueWrite("x");

	//Set the brightness
	dm->QueueWrite("B"+dm->ConvertNumToWritable(brightness));

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

	//Set time between color updates.
	dm->QueueWrite("d"+dm->ConvertNumToWritable(delay, true));
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
	settings.setValue("LinearBlending", linearBlending);
}

void PaletteForm::setSolidPalette(bool solidPalette)
{
	qDebug() << "Solid Palette:" << solidPalette;
	this->solidPalette = solidPalette;
	settings.setValue("SolidPalette", solidPalette);
}

void PaletteForm::setDelay(int delay)
{
	qDebug() << "Delay:" << delay;
	this->delay = delay;
	settings.setValue("Delay", delay);

}

void PaletteForm::setBrightness(int brightness)
{
	qDebug() << "Brightness:" << brightness;
	this->brightness = brightness;
	settings.setValue("Brightness", brightness);
}

void PaletteForm::testCustomPalette()
{
	//Cr255g000b000#r127g127b127#r000g000b255#r000g000b000#r255g000b000#r127g127b127#r000g000b255#r000g000b000#r255g000b000#r255g000b000#r127g127b127#r127g127b127#r000g000b255#r000g000b255#r000g000b000#r000g000b000##
	//CrFFg00b00#r7Fg7Fb7F#r00g00bFF#r00g00b00#rFFg00b00#r7Fg7Fb7F#r00g00bFF#r00g00b00#rFFg00b00#rFFg00b00#r7Fg7Fb7F#r7Fg7Fb7F#r00g00bFF#r00g00bFF#r00g00b00#r00g00b00##
	DeviceManager::getInstance()->QueueWrite(
				"xC"
				"rFFg00b00#"
				"r7Fg7Fb7F#"
				"r00g00bFF#"
				"r00g00b00#"
				"rFFg00b00#"
				"r7Fg7Fb7F#"
				"r00g00bFF#"
				"r00g00b00#"
				"rFFg00b00#"
				"rFFg00b00#"
				"r7Fg7Fb7F#"
				"r7Fg7Fb7F#"
				"r00g00bFF#"
				"r00g00bFF#"
				"r00g00b00#"
				"r00g00b00#"
				"#x"
	);
}
