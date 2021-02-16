#ifndef STATICCOLORFORM_H
#define STATICCOLORFORM_H

#include <QObject>

/**
 * @brief Stores three ints for rgb color in a struct.
 */
struct RGBColor {
	int r;
	int g;
	int b;

	RGBColor(int r, int g, int b){
		this->r = r;
		this->g = g;
		this->b = b;
	}

	RGBColor(){
		r = 0; g = 0; b = 0;
	}
};

/**
 * @brief The backend interface for the static color UI.
 */
class StaticColorForm : public QObject
{
	Q_OBJECT
public:
	explicit StaticColorForm(QObject *parent = nullptr);

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

	/**
	 * @brief Converts an HSV pair to RGB.
	 * @param H Hue (0 - 360)
	 * @param S Saturation (0 - 1)
	 * @param V Value (Brightness) (0 - 1)
	 */
	RGBColor HSVtoRGB(float H, float S, float V);

public slots:
//Typically called from QML

	/**
	 * @brief Signalled when the apply button is pressed.
	 */
	void Apply();
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

};

#endif // STATICCOLORFORM_H
