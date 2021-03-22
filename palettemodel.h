#ifndef PALETTEMODEL_H
#define PALETTEMODEL_H

#include <QAbstractListModel>

class PaletteList;

class PaletteModel : public QAbstractListModel
{
	Q_OBJECT
	Q_PROPERTY(PaletteList* list READ list WRITE setList)

public:
	explicit PaletteModel(QObject *parent = nullptr);

	enum {
		IDRole,
		NameRole,
		ColorsRole
	};

	// Basic functionality:
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	/*
	// Editable:
	bool setData(const QModelIndex &index, const QVariant &value,
				 int role = Qt::EditRole) override;
	Qt::ItemFlags flags(const QModelIndex &index) const override;
	*/

	virtual QHash<int, QByteArray> roleNames() const override;

	PaletteList *list() const;
	void setList(PaletteList *list);

private:
	PaletteList* mList;
};

#endif // PALETTEMODEL_H
