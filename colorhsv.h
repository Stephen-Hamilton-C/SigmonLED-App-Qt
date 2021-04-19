#ifndef COLORHSV_H
#define COLORHSV_H

class ColorRGB;
class QString;

/**
 * @brief Stores three doubles for hue, saturation, and value (brightness).
 * @author Stephen Hamilton
 */
class ColorHSV
{
public:
    /**
     * @brief Creates an empty HSV, which is black.
     */
    ColorHSV(){
        h = 0; s = 0; v = 0;
    };

    /**
     * @brief Creates a new HSV color
     * @param hue Hue (0 - 360)
     * @param saturation Saturation (0 - 1)
     * @param value Value (Brightness) (0 - 1)
     */
    ColorHSV(double hue, double saturation, double value){
        h = hue;
        s = saturation;
        v = value;
    }

    /**
     * @brief The hue channel. 0 - 360
     */
    double h;
    /**
     * @brief The saturation channel. 0 - 1
     */
    double s;
    /**
     * @brief The value (brightness) channel. 0 - 1
     */
    double v;

    /**
     * @brief Converts an RGB color into HSV
     * @param R Red channel
     * @param G Green channel
     * @param B Blue channel
     */
    static ColorHSV fromRGB(int R, int G, int B);
    /**
     * @brief Converts an RGB color into HSV
     * @param rgb The RGB color to convert
     * @return
     */
    static ColorHSV fromRGB(ColorRGB rgb);
    /**
     * @brief Converts a HEX string into HSV
     * @param hexString The HEX string, without the # at the start.
     */
    static ColorHSV fromHEX(QString hexString);

    QString toString();
};

#endif // COLORHSV_H
