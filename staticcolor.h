#ifndef STATICCOLOR_H
#define STATICCOLOR_H

#include <QObject>

class QTimer;

class StaticColor : public QObject
{
	Q_OBJECT
public:
	explicit StaticColor(QObject *parent = nullptr);

public slots:

	/**
	 * @brief Signalled when the apply button is pressed.
	 */
	void apply(double h, double s, double v);

    void hueChanged(double hue);
    void satChanged(double sat);
    void valChanged(double val);

private slots:

    void update();

private:

    QTimer* updateTimer;

    double h;
    double s;
    double v;

signals:

};

#endif // STATICCOLOR_H
