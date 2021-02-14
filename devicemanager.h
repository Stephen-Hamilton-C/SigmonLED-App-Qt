#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QString>
#include <QMap>
#include <QColor>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>

class DeviceManager : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QStringList devices READ devices NOTIFY DevicesChanged)

public:

	explicit DeviceManager(QObject *parent = nullptr);
	~DeviceManager();

	/**
	 * @brief Writes a command to the currently connected device
	 * @param cmd The command to write to the device
	 */
	void QueryWrite(const QString cmd);
	static QString ConvertNumToWritable(int num, const bool thousand = false);
	void ConnectToDevice(const QBluetoothDeviceInfo &device);

	QBluetoothDeviceInfo currentDevice;
	QBluetoothDeviceInfo testDevice;

	static DeviceManager* getInstance(){
		return ptrInstance;
	}

	QLowEnergyService* bleSerialService;
	QLowEnergyCharacteristic bleSerial;

private slots:

	void DiscoveredDevice(const QBluetoothDeviceInfo &info);
	void Write();
	void Connected();
	void BLEServiceDiscovered(const QBluetoothUuid uuid);
	void BLEServiceDetailDiscovered(QLowEnergyService::ServiceState newState);

private:

	static DeviceManager* ptrInstance;

	void StartDiscovery();
	void StopDiscovery();
	void DiscoverDetails();

	QBluetoothDeviceDiscoveryAgent* bleDiscovery;
	QList<QBluetoothDeviceInfo> discoveredDevices;
	QLowEnergyController* bleController;
	//QLowEnergyService* bleSerialService;
	//QLowEnergyCharacteristic bleSerial;

	QString writeBuffer;

	/**
	 * @brief serviceUUID The Serial Terminal service for HM-10 BLE modules
	 */
	const QString serviceUUID = "{0000ffe0-0000-1000-8000-00805f9b34fb}";
	/**
	 * @brief charUUID The Serial Terminal write characteristic for HM-10 BLE modules
	 */
	const QString charUUID = "0000ffe1-0000-1000-8000-00805f9b34fb";
	const QString testDeviceAddress = "64:69:4E:80:23:4E";

	QStringList devices();


	//All this should be handled in HomeForm, it does not fit the design specs for this class
	/*
	int hue = 0;
	int sat = 0;
	int val = 255;

	//I think brightness should be left alone in the Arduino as it is controlled by HSV
	//int bright = 255;

	int delay = 10;

	const QMap<QString, QString> sigmonPalette {
		{"Rainbow", "r"},
		{"Rainbow Stripe", "R"},
		{"Cloud", "c"},
		{"Party", "p"},
		{"Ocean", "o"},
		{"Lava", "l"},
		{"Forest", "f"}
	};
	*/

signals:

	void DevicesChanged(QStringList devices);

};

//===================================================|
//mainwindow.h                                       |
//===================================================|
/*
private slots:

	void write();

	void foundDevice(const QBluetoothDeviceInfo &info);

	void on_onButton_clicked();

	void on_offButton_clicked();

	void foundSvc(const QBluetoothUuid uuid);

	void connected();

	void foundDetail(QLowEnergyService::ServiceState newState);

	void on_colorButton_clicked();

	void on_backButton_clicked();

	void on_redEdit_textEdited(const QString &arg1);

	void on_greenEdit_textEdited(const QString &arg1);

	void on_blueEdit_textEdited(const QString &arg1);

	void on_redSlider_valueChanged(int value);

	void on_greenSlider_valueChanged(int value);

	void on_blueSlider_valueChanged(int value);

	void on_brightnessSlider_valueChanged(int value);

	void on_brightnessEdit_textEdited(const QString &arg1);

	void on_applyButton_clicked();

	void on_palatteButton_clicked();

	void on_backButton_2_clicked();

	void on_paletteApplyButton_clicked();

	void on_delayEdit_textChanged(const QString &arg1);

private:

	QBluetoothDeviceDiscoveryAgent* agent;
	QBluetoothDeviceInfo device;
	QLowEnergyController* cont;
	QLowEnergyService* svc;
	QLowEnergyCharacteristic cmd;

	QString writeBuffer;

	const QString deviceAddress = "64:69:4E:89:FE:54";
	const QString serviceUUID = "0000ffe0-0000-1000-8000-00805f9b34fb";
	const QString charUUID = "0000ffe1-0000-1000-8000-00805f9b34fb";

	int red = 255;
	int green = 255;
	int blue = 255;
	int bright = 255;
	int delay = 10;

	void connectToDevice();

	void updateColorPreview();

	void sendToWriteBuffer(const QString data);
	QString convertToWriteable(int num, bool thousand);

	const QMap<QString, QString> sigmonPalette {
		{"Rainbow", "r"},
		{"Rainbow Stripe", "R"},
		{"Cloud", "c"},
		{"Party", "p"},
		{"Ocean", "o"},
		{"Lava", "l"},
		{"Forest", "f"}
	};

	const QMap<QString, QString> sigmonPaletteBlend {
		{"Linear Blending", "l"},
		{"No Blending", "n"}
	};
*/

#endif // DEVICEMANAGER_H
