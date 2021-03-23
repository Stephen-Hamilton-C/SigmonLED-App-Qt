#include "paletteeditorlist.h"

PaletteEditorList::PaletteEditorList(QObject *parent) : QObject(parent)
{
	mItems.append(PaletteEditorItem("1", "#ff0000"));
	mItems.append(PaletteEditorItem("2", "#7f7f7f"));
	mItems.append(PaletteEditorItem("3", "#0000ff"));
	mItems.append(PaletteEditorItem("4", "#000000"));
	mItems.append(PaletteEditorItem("5", "#ff0000"));
	mItems.append(PaletteEditorItem("6", "#7f7f7f"));
	mItems.append(PaletteEditorItem("7", "#0000ff"));
	mItems.append(PaletteEditorItem("8", "#000000"));
	mItems.append(PaletteEditorItem("9", "#ff0000"));
	mItems.append(PaletteEditorItem("10", "#ff0000"));
	mItems.append(PaletteEditorItem("11", "#7f7f7f"));
	mItems.append(PaletteEditorItem("12", "#7f7f7f"));
	mItems.append(PaletteEditorItem("13", "#0000ff"));
	mItems.append(PaletteEditorItem("14", "#0000ff"));
	mItems.append(PaletteEditorItem("15", "#000000"));
	mItems.append(PaletteEditorItem("16", "#000000"));
}

QVector<PaletteEditorItem> PaletteEditorList::items() const
{
	return mItems;
}

void PaletteEditorList::setItems(const QVector<PaletteEditorItem> &items)
{
	mItems = items;
}
