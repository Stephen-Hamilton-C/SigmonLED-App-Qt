#ifndef HOMEFORM_H
#define HOMEFORM_H

#include <QObject>

/**
 * @brief The backend interface for the devices UI.
 */
class HomeForm : public QObject
{
	Q_OBJECT

	//Exposes the device list property.
	Q_PROPERTY(QStringList devices MEMBER devices NOTIFY devicesChanged);
	//Exposes the highlightedDelegate so it can be used as a variable in QML. This is never changed in backend.
	Q_PROPERTY(QString highlightedDelegate MEMBER highlightedDelegate NOTIFY highlightedDelegateChanged);
	//Exposes the showAll variable so it can be written by QML.
	Q_PROPERTY(bool showAll READ showAll WRITE setShowAll NOTIFY showAllChanged);



public:
	explicit HomeForm(QObject *parent = nullptr);

private slots:

	/**
	 * @brief Connected to DeviceManager's DevicesUpdated.
	 * @param deviceNames A list of QStrings that is encoded with a device name and MAC address.
	 */
	void DeviceListUpdated(QStringList deviceNames);

public slots:
//Typically called by QML

	/**
	 * @brief Signalled by QML when the connect button is pressed.
	 */
	void connectPressed();
	/**
	 * @brief Signalled by QML when a test connection is desired.
	 */
	void connectToTestDevice();

private:

//Constants:
	/**
	 * @brief The first three groupings of the MAC address to show in the default list.
	 * Any device not starting with these three groups is not shown unless m_ShowAll is true.
	 */
	const QString idMACType = "64:69:4E";

//Variables:
	/**
	 * @brief A list of QStrings that is encoded with a device name and MAC address.
	 */
	QStringList devices;
	/**
	 * @brief A variable held for QML. Just keeps track of which item is selected.
	 */
	QString highlightedDelegate;
	/**
	 * @brief Determines if all devices are shown or just devices with the first three MAC groupings defined in idMACType.
	 */
	bool m_ShowAll = false;

//Methods:
	/**
	 * @brief QML getter for m_ShowAll.
	 */
	bool showAll();
	/**
	 * @brief QML setter for m_ShowAll.
	 */
	void setShowAll(bool showAll);

signals:

	/**
	 * @brief Emitted when the device list is updated.
	 */
	void devicesChanged(QStringList devices);
	/**
	 * @brief Emitted when the highlighted delegate is changed, which is never, by the way. Not from here anyway.
	 */
	void highlightedDelegateChanged();
	/**
	 * @brief Emitted when m_ShowAll is changed.
	 */
	void showAllChanged(bool showAll);

};

#endif // HOMEFORM_H
