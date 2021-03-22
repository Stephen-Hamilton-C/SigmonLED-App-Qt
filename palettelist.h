#ifndef PALETTELIST_H
#define PALETTELIST_H

#include <QObject>
#include <QVariantList>

struct PaletteItem {
	QString name;
	QString uuid;
	QVariantList colors;
};

class PaletteList : public QObject
{
	Q_OBJECT
public:
	explicit PaletteList(QObject *parent = nullptr);

	QVector<PaletteItem> items() const;
	void setItems(const QVector<PaletteItem> &items);

	//bool setItemAt(int index, const PaletteItem &item);

private:

	QVector<PaletteItem> mItems;

signals:
	/*
	void preItemAppended();
	void postItemAppended();

	void preItemRemoved(int index);
	void postItemRemoved();
	*/
};

#endif // PALETTELIST_H
