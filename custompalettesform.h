#ifndef CUSTOMPALETTESFORM_H
#define CUSTOMPALETTESFORM_H

#include "palette.h"
#include "palettelist.h"

#include <QObject>
#include <QSettings>

class CustomPalettesForm : public QObject
{
	Q_OBJECT
	Q_PROPERTY(PaletteList* list READ getList WRITE setList NOTIFY listChanged)
	Q_PROPERTY(bool sendingPalette READ getSendingPalette WRITE setSendingPalette NOTIFY sendingPaletteChanged)
	Q_PROPERTY(double sendingProgress READ getSendingProgress WRITE setSendingProgress NOTIFY sendingProgressChanged)

public:
	explicit CustomPalettesForm(QObject *parent = nullptr);

	PaletteList *getList() const;
	void setList(PaletteList *value);

	bool getSendingPalette() const;
	void setSendingPalette(bool value);

public slots:
	void refreshPalettes();
	void newPalette();
	void delPalette(QString id);
	void uploadPalette(QString id);

private slots:
	void writeBufferUpdated(QString writeBuffer);

private:
	QMap<QString, Palette*> palettes;
	QSettings settings;

	PaletteList* list;

	bool activateProgress = false;
	bool sendingPalette = false;
	double sendingProgress = 0;
	int startingLength = 0;

signals:
	void modelChanged();
	void listChanged();
};

#endif // CUSTOMPALETTESFORM_H
