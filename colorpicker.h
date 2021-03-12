#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QObject>
#include <QSettings>

/**
 * @brief The backend interface for the static color UI.
 */
class ColorPicker : public QObject
{
	Q_OBJECT
    Q_PROPERTY(int hue MEMBER hue NOTIFY hueChanged)
    Q_PROPERTY(int saturation MEMBER saturation NOTIFY saturationChanged)
    Q_PROPERTY(int brightness MEMBER value NOTIFY brightnessChanged)

public:
	explicit ColorPicker(QObject *parent = nullptr);
	~ColorPicker();

private:

	/**
	 * @brief The hue entered from UI.
	 */
    int hue = 0;
	/**
	 * @brief The saturation entered from UI.
	 */
    int saturation = 0;
	/**
	 * @brief The brightness (value) entered from UI.
	 */
    int value = 255;

    QString settingName;
	QSettings settings;

public slots:

    void setSettingName(QString name);
    void saveSettings();

signals:
	void hueChanged(int hue);
	void saturationChanged(int saturation);
	void brightnessChanged(int brightness);

};

#endif // COLORPICKER_H
