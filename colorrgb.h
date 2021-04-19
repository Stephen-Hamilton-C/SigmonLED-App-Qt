#ifndef COLORRGB_H
#define COLORRGB_H

#include <QString>

class ColorHSV;

/**
 * @brief Stores three ints for red, green, and blue.
 * @author Stephen Hamilton
 */
class ColorRGB {

public:

    /**
     * @brief The stored red channel.
     */
    int r;
    /**
     * @brief The stored green channel.
     */
    int g;
    /**
     * @brief The stored blue channel.
     */
    int b;

    /**
     * @brief Creates a new RGB color.
     * @param red Red channel (0 - 255)
     * @param green Green channel (0 - 255)
     * @param blue Blue channel (0 - 255)
     */
    ColorRGB(int red, int green, int blue){
        r = red;
        g = green;
        b = blue;
	}

    /**
     * @brief Creates a blank RGB color, which is black.
     */
	ColorRGB(){
		r = 0; g = 0; b = 0;
	}

	/**
     * @brief Converts an HSV color to RGB.
	 * @param H Hue (0 - 360)
	 * @param S Saturation (0 - 1)
	 * @param V Value (Brightness) (0 - 1)
	 */
    static ColorRGB fromHSV(double H, double S, double V);
    /**
     * @brief Converts an HSV color to RGB.
     * @param hsv The HSV color to convert
     * @return
     */
    static ColorRGB fromHSV(ColorHSV hsv);
    /**
     * @brief Converts a HEX string into RGB
     * @param hexString The HEX string, without the # at the start.
     */
	static ColorRGB fromHEX(QString hexString);
    /**
     * @brief Converts a hexadecimal channel into an RGB channel.
     * @param hexChannel Two hexadecimal digits
     */
    static int hexChannelToColor(QString hexChannel);

    QString toString();

private:

    /**
     * @brief Converts a hexadecimal character into decimal
     * @param hexChar a single hexadecimal digit
     */
    static int hexCharToInt(QChar hexChar);

};

#endif // COLORRGB_H
