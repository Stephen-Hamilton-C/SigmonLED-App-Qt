#include "palettelist.h"
#include "palettemodel.h"
#include "palette.h"

PaletteList::PaletteList(QObject *parent) : QObject(parent) {}

QVector<PaletteItem> PaletteList::items() const
{
	return mItems;
}

void PaletteList::setItems(const QVector<PaletteItem> &items)
{
	mItems = items;
}

/*
bool PaletteList::setItemAt(int index, const PaletteItem &item)
{
	if(index < 0 || index >= mItems.size())
		return false;

	const PaletteItem &oldItem = mItems.at(index);
	if(oldItem.name == item.name && oldItem.uuid == item.uuid && oldItem.colors == item.colors)
		return false;

	mItems[index] = item;
	return true;
}

void PaletteList::appendItem()
{
	emit preItemAppended();

	PaletteItem item;
	item.name = "New Palette";
	item.uuid = "{INVALID}";
	item.colors = Palette::defaultColors;
	mItems.append(item);

	emit postItemAppended();
}
*/
