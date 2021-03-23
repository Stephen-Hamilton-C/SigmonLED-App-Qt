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

	double getSendingProgress() const;
	void setSendingProgress(double value);

	static QMap<QString, Palette*> palettes;

public slots:
	void refreshPalettes();
	QString newPalette();
	void delPalette(QString id);
	void uploadPalette(QString id);

private slots:
	void writeBufferUpdated(QString writeBuffer);

private:
	QSettings settings;

	PaletteList* list;

	bool activateProgress = false;
	bool sendingPalette = false;
	double sendingProgress = 0;
	int startingLength = 0;

signals:
	void modelChanged();
	void listChanged();
	void sendingPaletteChanged(bool sendingPalette);
	void sendingProgressChanged(double sendingProgress);
};

#endif // CUSTOMPALETTESFORM_H
