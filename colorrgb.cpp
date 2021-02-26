#include "ColorRGB.h"

#include <QDebug>
#include <math.h>

//Source: https://www.codespeedy.com/hsv-to-rgb-in-cpp/
ColorRGB ColorRGB::HSVtoRGB(float H, float S,float V){
	//if(H>360 || H<0 || S>100 || S<0 || V>100 || V<0){
	if(H>360 || H<0 || S>1 || S<0 || V>1 || V<0){
		//Return an empty color if color is invalid
		qDebug() << "The given HSV values are not in valid range";
		return ColorRGB();
	}

	//float s = S/100;
	//float v = V/100;
	float s = S;
	float v = V;
	float C = s*v;
	float X = C*(1-abs(fmod(H/60.0, 2)-1));
	float m = v-C;
	float r,g,b;
	if(H >= 0 && H < 60){
		r = C,g = X,b = 0;
	}
	else if(H >= 60 && H < 120){
		r = X,g = C,b = 0;
	}
	else if(H >= 120 && H < 180){
		r = 0,g = C,b = X;
	}
	else if(H >= 180 && H < 240){
		r = 0,g = X,b = C;
	}
	else if(H >= 240 && H < 300){
		r = X,g = 0,b = C;
	}
	else{
		r = C,g = 0,b = X;
	}

	int R = qRound((r+m)*255);
	int G = qRound((g+m)*255);
	int B = qRound((b+m)*255);

	return ColorRGB(R, G, B);
}
