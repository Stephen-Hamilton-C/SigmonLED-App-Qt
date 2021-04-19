#include "colorhsv.h"
#include "colorrgb.h"

#include <math.h>

//Source: https://stackoverflow.com/a/6930407
ColorHSV ColorHSV::fromRGB(int R, int G, int B)
{
    ColorHSV out;

    double      min, max, delta;

    min = R < G ? R : G;
    min = min  < B ? min  : B;

    max = R > G ? R : G;
    max = max  > B ? max  : B;

    out.v = max;                                // v
    delta = max - min;
    if (delta < 0.00001)
    {
        out.s = 0;
        out.h = 0; // undefined, maybe nan?

        out.s *= 255;

        return out;
    }
    if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        out.s = (delta / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0
        // s = 0, h is undefined
        out.s = 0.0;
        out.h = NAN;                            // its now undefined

        out.s *= 255;

        return out;
    }
    if( R >= max )                           // > is bogus, just keeps compilor happy
        out.h = ( G - B ) / delta;        // between yellow & magenta
    else
    if( G >= max )
        out.h = 2.0 + ( B - R ) / delta;  // between cyan & yellow
    else
        out.h = 4.0 + ( R - G ) / delta;  // between magenta & cyan

    out.h *= 60.0;                              // degrees

    if( out.h < 0.0 )
        out.h += 360.0;

    out.s *= 255;

    return out;
}

ColorHSV ColorHSV::fromRGB(ColorRGB rgb)
{
    return fromRGB(rgb.r, rgb.g, rgb.b);
}

ColorHSV ColorHSV::fromHEX(QString hexString)
{
    //Red channel
    QString redStr = QString(hexString.at(1))+QString(hexString.at(2));
    int red = ColorRGB::hexChannelToColor(redStr);

    //Green channel
    QString greenStr = QString(hexString.at(3))+QString(hexString.at(4));
    int green = ColorRGB::hexChannelToColor(greenStr);

    //Blue channel
    QString blueStr = QString(hexString.at(5))+QString(hexString.at(6));
    int blue = ColorRGB::hexChannelToColor(blueStr);

    //Convert RGB to HSV
    return fromRGB(red, green, blue);
}

QString ColorHSV::toString()
{
    return "H:"+QString::number(h)+","+
           "S:"+QString::number(s)+","+
           "V:"+QString::number(v);
}
