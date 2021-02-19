#include "staticcolorform.h"
#include "devicemanager.h"

#include <math.h>

StaticColorForm::StaticColorForm(QObject *parent) : QObject(parent) {}

void StaticColorForm::Apply()
{
	qDebug() << "Apply";

	//Convert from HSV to RGB. See header def for HSVtoRGB for argument ranges.
	RGBColor color = HSVtoRGB(h, s/255.0, v/255.0);

	DeviceManager* dm = DeviceManager::getInstance();
	//Set full brightness as this will effectively be controlled by HSV
	dm->QueueWrite("B255");

	//Set RGB
	dm->QueueWrite("r"+dm->ConvertNumToWritable(color.r));
	dm->QueueWrite("g"+dm->ConvertNumToWritable(color.g));
	dm->QueueWrite("b"+dm->ConvertNumToWritable(color.b));
}

void StaticColorForm::setH(int h)
{
	qDebug() << "Hue:" << h;
	this->h = h;
}

void StaticColorForm::setS(int s)
{
	qDebug() << "Saturation:" << s;
	this->s = s;
}

void StaticColorForm::setV(int v)
{
	qDebug() << "Value:" << v;
	this->v = v;
}

//Source: https://www.codespeedy.com/hsv-to-rgb-in-cpp/
RGBColor StaticColorForm::HSVtoRGB(float H, float S,float V){
	//if(H>360 || H<0 || S>100 || S<0 || V>100 || V<0){
	if(H>360 || H<0 || S>1 || S<0 || V>1 || V<0){
		//Return an empty color if color is invalid
		qDebug() << "The givem HSV values are not in valid range";
		return RGBColor();
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

	return RGBColor(R, G, B);
}
