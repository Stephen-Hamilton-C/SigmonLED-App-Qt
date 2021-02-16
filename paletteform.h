#ifndef PALETTEFORM_H
#define PALETTEFORM_H

#include <QObject>
#include <QMap>

/**
 * @brief The backend interface for the palette UI.
 */
class PaletteForm : public QObject
{
	Q_OBJECT

public:
	explicit PaletteForm(QObject *parent = nullptr);

public slots:
//Typically called from QML

	/**
	 * @brief Signalled when the apply button is pressed.
	 */
	void ApplyChanges();
	/**
	 * @brief Signalled when the palette is set.
	 * @param palette The text of the palette combobox. Put this through the sigmonPalette map to write.
	 */
	void setPalette(QString palette);
	/**
	 * @brief Signalled when the linear blending is set.
	 */
	void setLinearBlending(bool linearBlending);
	/**
	 * @brief Signalled when the solid palette is set.
	 */
	void setSolidPalette(bool solidPalette);
	/**
	 * @brief Signalled when the delay is set.
	 */
	void setDelay(int delay);
	/**
	 * @brief Signalled when the brightness is set.
	 */
	void setBrightness(int brightness);

private:

//Constants:
	/**
	  * @brief Maps combobox text to a char the SigmonLED Arduino expects for that palette
	*/
	const QMap<QString, QString> sigmonPalette {
		{"Rainbow", "r"},
		{"Rainbow Stripe", "R"},
		{"Cloud", "c"},
		{"Party", "p"},
		{"Ocean", "o"},
		{"Lava", "l"},
		{"Forest", "f"}
	};

//Variables:
	/**
	 * @brief Send an l (true) or an n (false) for linear blending
	 */
	bool linearBlending = true;
	/**
	 * @brief Send a P (true) or a p (false) for solid palette mode
	 */
	bool solidPalette = false;
	/**
	 * @brief The brightness of the LEDs, from 000 to 255. Should be a SigmonLED writable number
	 */
	QString brightness = "255";
	/**
	 * @brief The delay in ms between each color progression, from 0000 to 9999. Should be a SigmonLED thousand writable number
	 */
	QString delay = "0010";
	/**
	 * @brief The palette char
	 */
	QString palette = "r";


};

#endif // PALETTEFORM_H
