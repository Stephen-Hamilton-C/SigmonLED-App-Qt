#ifndef FASTONOFF_H
#define FASTONOFF_H

#include <QObject>

class FastOnOff : public QObject
{
	Q_OBJECT
public:
	explicit FastOnOff(QObject *parent = nullptr);

public slots:
	void on();
	void off();

signals:

};

#endif // FASTONOFF_H
