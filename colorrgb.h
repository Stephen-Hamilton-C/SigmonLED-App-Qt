#ifndef COLORRGB_H
#define COLORRGB_H

#include <QString>

/**
 * @brief Stores three ints for rgb color in a struct.
 */
class ColorRGB {

public:

	double r;
	double g;
	double b;

	ColorRGB(double r, double g, double b){
		this->r = r;
		this->g = g;
		this->b = b;
	}

	ColorRGB(){
		r = 0; g = 0; b = 0;
	}

	/**
	 * @brief Creates an RGB color from HSV.
	 * @param H Hue (0 - 360)
	 * @param S Saturation (0 - 1)
	 * @param V Value (Brightness) (0 - 1)
	 */
	static ColorRGB fromHSV(float H, float S, float V);
	static ColorRGB fromHSV(ColorRGB hsv);

	static ColorRGB toHSV(float R, float G, float B);
	static ColorRGB toHSV(ColorRGB rgb);

	QString toString();

	static ColorRGB fromHEX(QString hexString);

private:

	static int hexChannelToColor(QString hexChannel);
	static int hexCharToInt(QChar hexChar);

};

#endif // COLORRGB_H
