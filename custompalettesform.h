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

public:
	explicit CustomPalettesForm(QObject *parent = nullptr);

	PaletteList *getList() const;
	void setList(PaletteList *value);

public slots:
	void refreshPalettes();
	void newPalette();
	void delPalette(QString id);
	void uploadPalette(QString id);

private:
	QMap<QString, Palette*> palettes;
	QSettings settings;

	PaletteList* list;


signals:
	void modelChanged();
	void listChanged();
};

#endif // CUSTOMPALETTESFORM_H
