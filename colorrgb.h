#ifndef COLORRGB_H
#define COLORRGB_H

/**
 * @brief Stores three ints for rgb color in a struct.
 */
class ColorRGB {

public:

	int r;
	int g;
	int b;

	ColorRGB(int r, int g, int b){
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
	static ColorRGB HSVtoRGB(float H, float S, float V);

};

#endif // COLORRGB_H
