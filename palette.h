#ifndef PALETTE_H
#define PALETTE_H

#include <QObject>
#include <QColor>
#include <QSettings>

class Palette : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QVariantList colors READ getColors NOTIFY colorsChanged)
	Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(QString id READ getId NOTIFY idChanged)

public:
	explicit Palette(QObject *parent = nullptr);

	void upload();

	void save();
	void load(QString id);
	void del();

	QVariantList getColors(){
		return colors;
	};
	QString getName(){
		return name;
	}
	QString getId(){
		return id;
	}

	void setName(QString name){
		this->name = name;
	}

private:
	QVariantList colors;
	QString name = "New Palette";
	QString id;
	QSettings settings;

	static QVariantList defaultColors;

signals:
	void colorsChanged(QVariantList colors);
	void nameChanged(QString name);
	void idChanged(QString id);

};

#endif // PALETTE_H
