#include "paletteform.h"
#include "devicemanager.h"

#include <QTimer>

//Singleton
PaletteForm* PaletteForm::ptrInstance = nullptr;

PaletteForm::PaletteForm(QObject *parent)
{
    //Singleton
    if(ptrInstance != nullptr){
        delete this;
    }
    ptrInstance = this;

	linearBlending = settings.value("LinearBlending", true).toBool();
    solidPalette = settings.value("SolidPalette", false).toBool();
	delay = settings.value("Delay", 10).toInt();
    stretching = settings.value("Stretching", 3).toInt();

    palette = settings.value("Palette", "r").toString();

	QTimer::singleShot(100, this, [this]{
		emit linearBlendingChanged(linearBlending);
		emit solidPaletteChanged(solidPalette);
		emit delayChanged(delay);
        emit stretchingChanged(stretching);
        emit paletteIndexChanged(sigmonIndex[palette]);
	});

    dm = DeviceManager::getInstance();

    brightnessWriteTimer = new QTimer(this);
    connect(brightnessWriteTimer, &QTimer::timeout, this, &PaletteForm::writeBrightness);
}

void PaletteForm::customPaletteMode()
{
    palette = "C";
    settings.setValue("Palette", "C");
    emit paletteIndexChanged(sigmonIndex[palette]);
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

    //Set stretching
    dm->QueueWrite("s"+QString(dm->intToHex(stretching-1)));
}

void PaletteForm::setPalette(QString palette)
{
	qDebug() << "Palette:" << palette;
	this->palette = sigmonPalette[palette];
    settings.setValue("Palette", this->palette);

    dm->QueueWrite((solidPalette ? "P" : "p") + this->palette);
}

void PaletteForm::setLinearBlending(bool linearBlending)
{
	qDebug() << "Blending:" << linearBlending;
	this->linearBlending = linearBlending;
	settings.setValue("LinearBlending", linearBlending);
    dm->QueueWrite((linearBlending ? "l" : "n"));
}

void PaletteForm::setSolidPalette(bool solidPalette)
{
	qDebug() << "Solid Palette:" << solidPalette;
	this->solidPalette = solidPalette;
	settings.setValue("SolidPalette", solidPalette);

    dm->QueueWrite((solidPalette ? "P" : "p") + palette);
}

void PaletteForm::setDelay(int delay)
{
	qDebug() << "Delay:" << delay;
	this->delay = delay;
	settings.setValue("Delay", delay);

    dm->QueueWrite("d"+dm->ConvertNumToWritable(delay, true));
}

void PaletteForm::setBrightness(int brightness)
{
	qDebug() << "Brightness:" << brightness;
	this->brightness = brightness;

    brightnessWriteTimer->start(100);
}

void PaletteForm::setStretching(int stretching)
{
    qDebug() << "Stretching:" << stretching;
    this->stretching = stretching;
    settings.setValue("Stretching", stretching);

    dm->QueueWrite("s"+QString(dm->intToHex(stretching-1)));
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

void PaletteForm::writeBrightness()
{
    dm->QueueWrite("B"+dm->ConvertNumToWritable(brightness));
    brightnessWriteTimer->stop();
}
