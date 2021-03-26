#ifndef PALETTE_H
#define PALETTE_H

#include "colorrgb.h"

#include <QObject>
#include <QColor>
#include <QSettings>

class Palette : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QVariantList colors MEMBER colors NOTIFY colorsChanged)
	Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(QString uuid MEMBER id NOTIFY idChanged)

public:
	explicit Palette(QObject *parent = nullptr);
	explicit Palette(QString id, QObject *parent = nullptr);

	int upload();

	QString toString();
	bool compare(Palette const &otherPalette) const;

	void save();
	void load(QString id);
	void del();

	QVariantList getColors() const{
		return colors;
	};
	QString getName() const{
		return name;
	}
	QString getId() const{
		return id;
	}

	void setName(const QString &name){
		this->name = name;
		settings.setValue("CustomPalettes/"+id+"/name", name);
	}

	static QVariantList defaultColors;

private:
	QVariantList colors;
	QString name = "New Palette";
	QString id;
	QSettings settings;

signals:
	void colorsChanged(QVariantList colors);
	void nameChanged(QString name);
	void idChanged(QString id);

};

#endif // PALETTE_H
