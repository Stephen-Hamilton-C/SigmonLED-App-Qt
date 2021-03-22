#include "palettemodel.h"
#include "palette.h"
#include "palettelist.h"

PaletteModel::PaletteModel(QObject *parent)
	: QAbstractListModel(parent)
	, mList(nullptr)
{
}

int PaletteModel::rowCount(const QModelIndex &parent) const
{
	// For list models only the root node (an invalid parent) should return the list's size. For all
	// other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
	if (parent.isValid() || !mList)
		return 0;

	return mList->items().size();
	// FIXME: Implement me!
}

QVariant PaletteModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid() || !mList)
		return QVariant();

	const PaletteItem item = mList->items().at(index.row());
	switch(role){
		case IDRole:
			return QVariant(item.uuid);
		case NameRole:
			return QVariant(item.name);
		case ColorsRole:
			return QVariant(item.colors);
	}

	return QVariant();
}

/*
bool PaletteModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if(!mList)
		return false;

	PaletteItem item = mList->items().at(index.row());
	switch(role){
		case IDRole:
			item.uuid = value.toString();
			break;
		case NameRole:
			item.name = value.toString();
			break;
		case ColorsRole:
			item.colors = value.toList();
			break;
	}

	if(mList->setItemAt(index.row(), item)){
		// FIXME: Implement me!
		emit dataChanged(index, index, QVector<int>() << role);
		return true;
	}
	return false;
}

Qt::ItemFlags PaletteModel::flags(const QModelIndex &index) const
{
	if(!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEditable;
}
*/

QHash<int, QByteArray> PaletteModel::roleNames() const
{
	QHash<int, QByteArray> names;
	names[IDRole] = "uuid";
	names[NameRole] = "name";
	names[ColorsRole] = "colors";
	return names;
}

PaletteList *PaletteModel::list() const
{
	return mList;
}

void PaletteModel::setList(PaletteList *list)
{
	beginResetModel();

	if(mList){
		mList->disconnect(this);
	}

	mList = list;

	/*
	if(mList){
		connect(mList, &PaletteList::preItemAppended, this, [=](){
			const int index = mList->items().size();
			beginInsertRows(QModelIndex(), index, index);
		});
		connect(mList, &PaletteList::postItemAppended, this, [=](){
			endInsertRows();
		});
		connect(mList, &PaletteList::preItemRemoved, this, [=](int index){
			beginRemoveRows(QModelIndex(), index, index);
		});
		connect(mList, &PaletteList::postItemRemoved, this, [=](){
			endRemoveRows();
		});
	}
	*/

	endResetModel();
}
