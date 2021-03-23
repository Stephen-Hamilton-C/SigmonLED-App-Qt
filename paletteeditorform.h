#ifndef PALETTEEDITORFORM_H
#define PALETTEEDITORFORM_H

#include "paletteeditorlist.h"

#include <QObject>

class Palette;

class PaletteEditorForm : public QObject
{
	Q_OBJECT
	Q_PROPERTY(PaletteEditorList* list READ getList WRITE setList NOTIFY listChanged)
	Q_PROPERTY(QString paletteID READ getPaletteID WRITE setPaletteID NOTIFY paletteIDChanged)
	Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)

public:
	explicit PaletteEditorForm(QObject *parent = nullptr);

	PaletteEditorList *getList() const;
	void setList(PaletteEditorList *value);

	QString getPaletteID() const;
	void setPaletteID(const QString &value);

	QString getName() const;
	void setName(const QString &value);

public slots:
	void savePalette();
	void refreshPalette();
	void editColor(int colorIndex);

private:

	Palette* currentPalette;
	PaletteEditorList* list;
	QString paletteID;

signals:
	void listChanged(PaletteEditorList* list);
	void paletteIDChanged(QString paletteID);
	void nameChanged(QString name);
	void colorIndexEdit(int colorIndex);
};

#endif // PALETTEEDITORFORM_H
