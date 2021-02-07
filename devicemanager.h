#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QString>
#include <QMap>
#include <QColor>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>

struct RGBColor {
public:
	int r;
	int g;
	int b;

	RGBColor(int hue, int sat, int val){
		QColor color = QColor::fromHsv(hue, sat, val);
		r = color.red();
		g = color.green();
		b = color.blue();
	}
};

class DeviceManager
{
	//Q_OBJECT

public:

	DeviceManager(QWidget *parent = nullptr);
	//~DeviceManager();

	/**
	 * @brief getSerial Gets a pointer to the serial write characteristic
	 * @return A pointer to the serial write characteristic
	 */
	/*
	QLowEnergyCharacteristic* getSerial() {
		return &bleSerial;
	};
	*/

	QBluetoothDeviceInfo currentDevice;

private slots:

	//void discoveredDevice(const QBluetoothDeviceInfo &info);

private:

	//void startDiscovery();

	//RGBColor convertHSVtoRGB(int hue, int sat, int val);


	QBluetoothDeviceDiscoveryAgent* bleDiscovery;
	QList<QBluetoothDeviceInfo> discoveredDevices;
	QLowEnergyController* bleController;
	QLowEnergyService* bleSerialService;
	QLowEnergyCharacteristic bleSerial;

	/**
	 * @brief serviceUUID The Serial Terminal service for HM-10 BLE modules
	 */
	const QString serviceUUID = "0000ffe0-0000-1000-8000-00805f9b34fb";
	/**
	 * @brief charUUID The Serial Terminal write character for HM-10 BLE modules
	 */
	const QString charUUID = "0000ffe1-0000-1000-8000-00805f9b34fb";

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
