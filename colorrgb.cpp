#include "colorrgb.h"
#include "colorhsv.h"

#include <QDebug>
#include <math.h>

//Source: https://www.codespeedy.com/hsv-to-rgb-in-cpp/
ColorRGB ColorRGB::fromHSV(double H, double S, double V){
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

ColorRGB ColorRGB::fromHSV(ColorHSV hsv)
{
    return fromHSV(hsv.h, hsv.s, hsv.v);
}



ColorRGB ColorRGB::fromHEX(QString hexString)
{
	QString redStr = QString(hexString.at(1))+QString(hexString.at(2));
	int red = hexChannelToColor(redStr);

	QString greenStr = QString(hexString.at(3))+QString(hexString.at(4));
	int green = hexChannelToColor(greenStr);

	QString blueStr = QString(hexString.at(5))+QString(hexString.at(6));
	int blue = hexChannelToColor(blueStr);

	return ColorRGB(red, green, blue);
}

int ColorRGB::hexChannelToColor(QString hexChannel)
{
	int color = 0;
	int hexTens = hexCharToInt(hexChannel.at(0));
	int hexOnes = hexCharToInt(hexChannel.at(1));
	color = hexOnes + hexTens * 16;

	return color;
}

int ColorRGB::hexCharToInt(QChar hexChar)
{
	hexChar = hexChar.toUpper();
	if(hexChar == '1')
		return 1;
	if(hexChar == '2')
		return 2;
	if(hexChar == '3')
		return 3;
	if(hexChar == '4')
		return 4;
	if(hexChar == '5')
		return 5;
	if(hexChar == '6')
		return 6;
	if(hexChar == '7')
		return 7;
	if(hexChar == '8')
		return 8;
	if(hexChar == '9')
		return 9;
	if(hexChar == 'A')
		return 10;
	if(hexChar == 'B')
		return 11;
	if(hexChar == 'C')
		return 12;
	if(hexChar == 'D')
		return 13;
	if(hexChar == 'E')
		return 14;
	if(hexChar == 'F')
		return 15;


	return 0;
}

QString ColorRGB::toString()
{
	return "R:"+QString::number(r)+","+
			"G:"+QString::number(g)+","+
			"B:"+QString::number(b);
}
