#include "paletteeditormodel.h"
#include "paletteeditorlist.h"

PaletteEditorModel::PaletteEditorModel(QObject *parent)
	: QAbstractListModel(parent)
	, mList(nullptr)
{
}

int PaletteEditorModel::rowCount(const QModelIndex &parent) const
{
	// For list models only the root node (an invalid parent) should return the list's size. For all
	// other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
	if (parent.isValid() || !mList)
		return 0;

	return mList->items().size();
}

QVariant PaletteEditorModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid() || !mList)
		return QVariant();

	const PaletteEditorItem item = mList->items().at(index.row());
	switch(role){
		case IndexRole:
			return QVariant(item.index);
		case ColorRole:
			return QVariant(item.color);
	}

	return QVariant();
}

QHash<int, QByteArray> PaletteEditorModel::roleNames() const
{
	QHash<int, QByteArray> names;
	names[IndexRole] = "index";
	names[ColorRole] = "color";
	return names;
}

PaletteEditorList *PaletteEditorModel::list() const
{
	return mList;
}

void PaletteEditorModel::setList(PaletteEditorList *list)
{
	beginResetModel();

	if(mList){
		mList->disconnect(this);
	}

	mList = list;

	endResetModel();
}
