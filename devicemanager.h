#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>
#include <QTimer>
#include <QSettings>

/**
 * @brief DeviceManager is meant to handle connection between bluetooth devices.
 */
class DeviceManager : public QObject
{
	Q_OBJECT

	//Used to indicate connection status to QML
	Q_PROPERTY(bool connected MEMBER connected NOTIFY onBLEConnectedChanged)
	Q_PROPERTY(bool ready MEMBER ready NOTIFY onBLEReadyChanged)

public:

//Construct/Destruct:
	explicit DeviceManager(QObject *parent = nullptr);
	~DeviceManager();

	//Singleton
	static DeviceManager* getInstance(){
		return ptrInstance;
	}

//Methods:
	/**
	 * @brief Writes a command to the currently connected device. May take up to 35 ms to begin writing
	 * @param cmd The command to write to the device.
	 */
	void QueueWrite(const QString cmd);
	/**
	 * @brief Checks if the writeBuffer is empty
	 * @return
	 */
	bool doneWriting();
	/**
	 * @brief Converts an integer to a QString that can be written to a SigmonLED Arduino safely.
	 * Example: converts 64 into 064, 8 into 008.
	 * @param num The integer number to convert.
	 * @param thousand Whether or not this should be converted into a thousand number.
	 * Example: converts 250 into 0250, 50 into 0050.
	 * @return
	 */
	static QString ConvertNumToWritable(int num, const bool thousand = false);
	/**
	 * @brief Connects to a Bluetooth device using its info
	 * @param device The device to connect to
	 */
	void ConnectToDevice(const QBluetoothDeviceInfo &device);

//Variables:
	/**
	 * @brief Whether or not a device is currently connected.
	 */
	bool connected = false;
	/**
	 * @brief Whether or not a device is ready to be written to.
	 */
	bool ready = false;
	/**
	 * @brief The info object of the test Arduino I use, if it is discovered.
	 * This was used before the device list was implemented to ensure other aspects of the app were functional.
	 */
	QBluetoothDeviceInfo testDevice;
	/**
	 * @brief Makes it stupid easy for the frontend to tell the backend which device to connect to.
	 * The QString is the device's display name and the MAC address combined.
	 * The MAC address is chopped off in the frontend so the display name is all that's shown, however, it keeps track of the full name and address.
	 * When a connect is called, the HomeForm backend just maps the tracked name and address string to a QBluetoothDeviceInfo and then connects with that.
	 */
	QMap<QString, QBluetoothDeviceInfo> deviceMap;

private slots:

//BLE:
	/**
	 * @brief Signalled when the QBluetoothController finds a service to the newly connected device.
	 * @param uuid The UUID of the service.
	 */
	void BLEServiceDiscovered(const QBluetoothUuid uuid);
	/**
	 * @brief Signalled when the state of the serialService changes, this typically happens when characteristics are discovered.
	 * @param newState The state the service just entered.
	 */
	void BLEServiceDetailDiscovered(QLowEnergyService::ServiceState newState);
	/**
	 * @brief Signalled when a BLE error occurs.
	 * @param err The type of BLE error that occurred.
	 */
	void BLEError(QLowEnergyController::Error err);
	/**
	 * @brief Signalled when the QBluetoothDeviceDiscoveryAgent discovers a BLE device.
	 * @param info The information tied to the discovered device.
	 */
	void BLEDiscoveredDevice(const QBluetoothDeviceInfo &info);
	/**
	 * @brief Signalled when successfully connected to a Bluetooth device.
	 */
	void BLEConnected();
	/**
	 * @brief Signalled when disconnected from a Bluetooth device.
	 */
	void BLEDisconnected();

//Timer:
	/**
	 * @brief Signalled from the writeTimer every 35 ms. Writes one char from the writeBuffer.
	 * This prevents the sensitive Arduino serial from being overloaded.
	 */
	void Timer_Write();
	/**
	 * @brief Signalled by a singleshot QTimer. Discovers descriptors for the bleSerialService.
	 * This needs to be delayed by a few centiseconds so the serial characteristic can be found.
	 */
	void Timer_DiscoverServiceDetails();

public slots:
//These are typically called from QML

	/**
	 * @brief Clears currently discovered devices and looks for devices.
	 */
	void startDiscovery();
	/**
	 * @brief Stops looking for devices.
	 */
	void stopDiscovery();
	/**
	 * @brief Disconnects from the current device, if one is connected.
	 */
	void disconnectFromDevice();

private:

	//Singleton
	static DeviceManager* ptrInstance;

//Constants:
	/**
	 * @brief The Serial Terminal service for HM-10 BLE modules.
	 */
	const QString serviceUUID = "{0000ffe0-0000-1000-8000-00805f9b34fb}";
	/**
	 * @brief The Serial Terminal write characteristic for HM-10 BLE modules.
	 */
	const QString charUUID = "0000ffe1-0000-1000-8000-00805f9b34fb";
	/**
	 * @brief The MAC address of the test Arduino I use.
	 */
	const QString testDeviceAddress = "64:69:4E:80:23:4E";
	/**
	 * @brief The JSON key for storing the last connected MAC address
	 */
	const QString jsonLastMAC = "devices_LastConnectedMAC";

//Methods:
	/**
	 * @brief Converts the discoveredDevices list into a list of QStrings that have the device name and then the MAC address
	 */
	QStringList EncodeDevicesList();

//BLE:
	/**
	 * @brief An agent that searches for BLE devices to connect to
	 */
	QBluetoothDeviceDiscoveryAgent* bleDiscovery;
	/**
	 * @brief An interface to the Bluetooth device controller
	 */
	QLowEnergyController* bleController;
	/**
	 * @brief The BLE service used for serial communication with the Arduino.
	 */
	QLowEnergyService* bleSerialService;
	/**
	 * @brief The BLE characteristic on the bleSerialService used for serial communication.
	 */
	QLowEnergyCharacteristic bleSerial;

//Vars:
	/**
	 * @brief Determines if the discovery agent is currently searching for devices.
	 */
	bool discovering = false;
	/**
	 * @brief Determines if the controller should attempt to automatically connect to the last device connected to. Also determined by Settings.
	 */
	bool shouldReconnect = true;
	/**
	 * @brief Devices that have been discovered by the discovery agent.
	 */
	QList<QBluetoothDeviceInfo> discoveredDevices;
	/**
	 * @brief The device that is currently connected.
	 */
	QBluetoothDeviceInfo currentDevice;
	/**
	 * @brief A string of characters that are to be written to bleSerial. These chars are written in Timer_Write().
	 * This is set by QueueWrite().
	 */
	QString writeBuffer;
	//Literally won't even explain this. It doesn't need any.
	QSettings settings;

//Timers:
	/**
	 * @brief The timer that automatically stops discovery after a few seconds.
	 */
	QTimer* discoveryTimer;

signals:

	/**
	 * @brief Emitted when discoveredDevices is changed.
	 */
	void DevicesChanged(QStringList devices);
	/**
	 * @brief Emitted when discovery starts.
	 */
	void onBLEStartedSearch();
	/**
	 * @brief Emitted when discovery stops.
	 */
	void onBLEStoppedSearch();
	/**
	 * @brief Emitted when connected or disconnected. Bound to QML property.
	 */
	void onBLEConnectedChanged(bool connected);
	/**
	 * @brief Emitted when connected.
	 */
	void onBLEConnect();
	/**
	 * @brief Emitted when a connection is ready to write to.
	 */
	void onBLEReady();
	/**
	 * @brief Emitted when ready status is changed.
	 */
	void onBLEReadyChanged(bool ready);
	/**
	 * @brief Emitted when a connection is being attempted.
	 */
	void onBLEConnecting();
	/**
	 * @brief Emitted when disconnected.
	 */
	void onBLEDisconnect();
	/**
	 * @brief Emitted when a BLE error occurs.
	 */
	void onBLEFault(QString errMsg);

};

#endif // DEVICEMANAGER_H
