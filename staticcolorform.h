#ifndef STATICCOLORFORM_H
#define STATICCOLORFORM_H

#include <QObject>
#include <QColor>

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

class StaticColorForm : public QObject
{
	Q_OBJECT
public:
	explicit StaticColorForm(QObject *parent = nullptr);

private:

	int h = 0;
	int s = 0;
	int v = 255;

	RGBColor HSVtoRGB(float H, float S, float V);

public slots:

	void Apply();
	void setH(int h);
	void setS(int s);
	void setV(int v);

};

#endif // STATICCOLORFORM_H
