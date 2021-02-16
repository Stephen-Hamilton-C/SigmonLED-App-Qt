#ifndef FASTONOFF_H
#define FASTONOFF_H

#include <QObject>

/**
 * @brief Simple backend for the on/off RoundButtons in the corner
 */
class FastOnOff : public QObject
{
	Q_OBJECT
public:
	explicit FastOnOff(QObject *parent = nullptr);

public slots:
	/**
	 * @brief Signalled when the on button is pressed
	 */
	void on();
	/**
	 * @brief Signalled when the off button is pressed
	 */
	void off();

};

#endif // FASTONOFF_H
