#ifndef PALETTEFORM_H
#define PALETTEFORM_H

#include <QObject>
#include <QMap>
#include <QSettings>

class DeviceManager;
class QTimer;

/**
 * @brief The backend interface for the palette UI.
 */
class PaletteForm : public QObject
{
	Q_OBJECT

public:
	explicit PaletteForm(QObject *parent = nullptr);

    //Singleton
    static PaletteForm* getInstance(){
        return ptrInstance;
    }

    void customPaletteMode();

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
    void setStretching(int stretching);
	void testCustomPalette();

private slots:

    void writeBrightness();

private:

//Singleton
    static PaletteForm* ptrInstance;

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
		{"Forest", "f"},
		{"Custom", "C"}
	};

    const QMap<QString, int> sigmonIndex {
        {"r", 0},
        {"R", 1},
        {"c", 2},
        {"p", 3},
        {"o", 4},
        {"l", 5},
        {"f", 6},
        {"C", 7}
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
	 * @brief The brightness of the LEDs, from 0 to 255.
	 */
	int brightness = 255;
	/**
	 * @brief The delay in ms between each color progression, from 0 to 4095.
	 */
	int delay = 10;

    int stretching = 3;
	/**
	 * @brief The palette char
	 */
	QString palette = "r";

	QSettings settings;

	DeviceManager* dm;

    QTimer* brightnessWriteTimer;

signals:
    void paletteIndexChanged(int paletteIndex);
	void paletteChanged(QString palette);
	void delayChanged(int delay);
	void brightnessChanged(int brightness);
	void solidPaletteChanged(bool solidPalette);
	void linearBlendingChanged(bool linearBlending);
    void stretchingChanged(int stretching);

};

#endif // PALETTEFORM_H
