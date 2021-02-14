#ifndef PALETTEFORM_H
#define PALETTEFORM_H

#include <QObject>
#include <QMap>

class PaletteForm : public QObject
{
	Q_OBJECT

public:
	explicit PaletteForm(QObject *parent = nullptr);

public slots:

	void ApplyChanges();
	void setPalette(QString palette);
	void setLinearBlending(bool linearBlending);
	void setDelay(int delay);
	void setBrightness(int brightness);

private:

	QString palette = "r";
	bool linearBlending = true;
	QString brightness = "255";
	QString delay = "0010";

	const QMap<QString, QString> sigmonPalette {
		{"Rainbow", "r"},
		{"Rainbow Stripe", "R"},
		{"Cloud", "c"},
		{"Party", "p"},
		{"Ocean", "o"},
		{"Lava", "l"},
		{"Forest", "f"}
	};

};

#endif // PALETTEFORM_H
