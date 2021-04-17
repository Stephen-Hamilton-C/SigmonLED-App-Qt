#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QObject>
#include <QSettings>

/**
 * @brief The backend interface for the color picker UI
 * @author Stephen Hamilton
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

    /**
     * @brief The prefix of the QSettings that hold the hue, saturation, and brightness.
     */
    QString settingPrefix;
    /**
     * @brief QSettings interface with default scope
     */
	QSettings settings;

public slots:

    /**
     * @brief Sets the settingPrefix and updates the HSV values with the values stored in that QSetting
     * @param The prefix of the QSettings that hold the HSV values
     */
    void setSettingName(QString prefix);
    /**
     * @brief Sets the QSettings to current HSV values stored using the settingPrefix
     */
    void saveSettings();

signals:
	void hueChanged(int hue);
	void saturationChanged(int saturation);
	void brightnessChanged(int brightness);

};

#endif // COLORPICKER_H
