#ifndef PALETTECOLORMODEL_H
#define PALETTECOLORMODEL_H

#include <QObject>
#include <QColor>

class PaletteColorModel : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString labelText MEMBER labelText NOTIFY labelTextChanged)
	Q_PROPERTY(QColor boxColor MEMBER color NOTIFY colorChanged)
public:
	explicit PaletteColorModel(QString labelText, QColor color, QObject *parent = nullptr);

	QString labelText;
	QColor color;

signals:
	void labelTextChanged(QString labelText);
	void colorChanged(QColor color);

};

#endif // PALETTECOLORMODEL_H
