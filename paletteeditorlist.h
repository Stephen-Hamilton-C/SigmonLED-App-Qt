#ifndef PALETTEEDITORLIST_H
#define PALETTEEDITORLIST_H

#include <QObject>
#include <QColor>

struct PaletteEditorItem {
	QString index;
	QString color;

	PaletteEditorItem(QString index, QString color){
		this->index = index;
		this->color = color;
	}
};

class PaletteEditorList : public QObject
{
	Q_OBJECT
public:
	explicit PaletteEditorList(QObject *parent = nullptr);

	QVector<PaletteEditorItem> items() const;
	void setItems(const QVector<PaletteEditorItem> &items);

private:
	QVector<PaletteEditorItem> mItems;

signals:

};

#endif // PALETTEEDITORLIST_H
