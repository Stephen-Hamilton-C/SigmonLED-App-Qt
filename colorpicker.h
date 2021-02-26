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

public:
	explicit ColorPicker(QObject *parent = nullptr);
	~ColorPicker();

private:

	/**
	 * @brief The hue entered from UI.
	 */
	int h = 0;
	/**
	 * @brief The saturation entered from UI.
	 */
	int s = 0;
	/**
	 * @brief The brightness (value) entered from UI.
	 */
	int v = 255;

	QSettings settings;

public slots:
//Typically called from QML

	/**
	 * @brief Signalled when the hue is set in UI.
	 */
	void setH(int h);
	/**
	 * @brief Signalled when the saturation is set in UI.
	 */
	void setS(int s);
	/**
	 * @brief Signalled when the value (brightness) is set in the UI.
	 */
	void setV(int v);

signals:
	void hueChanged(int hue);
	void saturationChanged(int saturation);
	void brightnessChanged(int brightness);

};

#endif // COLORPICKER_H
