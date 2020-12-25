#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLowEnergyController>
#include <QBluetoothDeviceDiscoveryAgent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:

	void foundDevice(const QBluetoothDeviceInfo &info);

	void on_onButton_clicked();

	void on_offButton_clicked();

	void foundSvc(const QBluetoothUuid uuid);

	void connected();

	void foundDetail(QLowEnergyService::ServiceState newState);

private:
	Ui::MainWindow *ui;

	QBluetoothDeviceDiscoveryAgent* agent;
	QBluetoothDeviceInfo device;
	QLowEnergyController* cont;
	QLowEnergyService* svc;
	QLowEnergyCharacteristic cmd;

	const QString deviceAddress = "64:69:4E:89:FE:54";
	const QString serviceUUID = "0000ffe0-0000-1000-8000-00805f9b34fb";
	const QString charUUID = "0000ffe1-0000-1000-8000-00805f9b34fb";

	void connectToDevice();

};
#endif // MAINWINDOW_H
