#ifndef PALETTEEDITORMODEL_H
#define PALETTEEDITORMODEL_H

#include <QAbstractListModel>

#include "paletteeditorlist.h"

//class PaletteEditorList;

class PaletteEditorModel : public QAbstractListModel
{
	Q_OBJECT
	Q_PROPERTY(PaletteEditorList* list READ list WRITE setList)

public:
	explicit PaletteEditorModel(QObject *parent = nullptr);

	enum {
		IndexRole,
		ColorRole
	};

	// Basic functionality:
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	virtual QHash<int, QByteArray> roleNames() const override;

	PaletteEditorList *list() const;
	void setList(PaletteEditorList *list);

private:
	PaletteEditorList* mList;
};

#endif // PALETTEEDITORMODEL_H
