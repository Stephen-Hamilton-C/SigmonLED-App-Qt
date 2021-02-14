#include "devicemanager.h"
#include <QTimer>

DeviceManager* DeviceManager::ptrInstance = nullptr;

DeviceManager::DeviceManager(QObject *parent)
{
	if(ptrInstance != nullptr){
		delete this;
	}
	ptrInstance = this;

	bleDiscovery = new QBluetoothDeviceDiscoveryAgent();
	connect(bleDiscovery, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &DeviceManager::DiscoveredDevice);

	QTimer* timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &DeviceManager::Write);
	timer->start(35);

	//This line is causing init crash
	discoveryTimer = new QTimer(this);
	connect(discoveryTimer, &QTimer::timeout, this, &DeviceManager::stopDiscovery);
	qDebug() << "DeviceManager constructed";

	startDiscovery();
}

DeviceManager::~DeviceManager()
{
	stopDiscovery();
	bleController->disconnectFromDevice();
}

void DeviceManager::QueryWrite(const QString cmd)
{
	writeBuffer += cmd;
}

QString DeviceManager::ConvertNumToWritable(int num, const bool thousand)
{
	QString val;

	if(num >= 1000){
		val += QString::number(floor(num/1000));
		num -= floor(num/1000)*1000;
	} else if(thousand){
		val += "0";
	}

	if(num >= 100){
		val += QString::number(floor(num/100));
		num -= floor(num/100)*100;
	} else {
		val += "0";
	}

	if(num >= 10){
		val += QString::number(floor(num/10));
		num -= floor(num/10)*10;
	} else {
		val += "0";
	}

	val += QString::number(num);

	return val;
}

void DeviceManager::ConnectToDevice(const QBluetoothDeviceInfo &device)
{
	//Alert QML that we are connecting
	emit onConnecting();
	qDebug() << "Connecting to "+device.name()+"...";
	if(connected){
		disconnectFromDevice();
	}
	bleController = QLowEnergyController::createCentral(device, this);

	connect(bleController, &QLowEnergyController::connected, this, &DeviceManager::Connected);

	currentDevice = device;
	bleController->setRemoteAddressType(QLowEnergyController::PublicAddress);
	bleController->connectToDevice();
}

void DeviceManager::Connected(){
	//Alert QML we are connected
	qDebug() << "Connected to "+currentDevice.name();

	connect(bleController, &QLowEnergyController::serviceDiscovered, this, &DeviceManager::BLEServiceDiscovered);
	connect(bleController, &QLowEnergyController::disconnected, this, &DeviceManager::Disconnected);
	bleController->discoverServices();
	connected = true;
	emit onConnected();
	emit onConnectedChanged(connected);
}

void DeviceManager::Disconnected()
{
	connected = false;
	emit onDisconnected();
	emit onConnectedChanged(connected);
}

void DeviceManager::BLEServiceDiscovered(const QBluetoothUuid uuid)
{
	qDebug() << "Service discovered:" << uuid.toString();
	if(uuid.toString() == serviceUUID){
		qDebug() << "---This is the serial service---";
		bleSerialService = bleController->createServiceObject(uuid, this);

		connect(bleSerialService, &QLowEnergyService::stateChanged, this, &DeviceManager::BLEServiceDetailDiscovered);
		QTimer::singleShot(50, this, &DeviceManager::DiscoverDetails);
	}
}

void DeviceManager::BLEServiceDetailDiscovered(QLowEnergyService::ServiceState newState)
{
	qDebug() << "Detail discovered";
	bleSerial = bleSerialService->characteristic(QBluetoothUuid(charUUID));
	qDebug() << "Serial valid:" << bleSerial.isValid();
	//Alert QML that we are ready. Check if the char is actually valid first.

}

void DeviceManager::BLEError(QLowEnergyController::Error errMsg)
{
	qDebug() << "BLE Error:" << errMsg;
	switch(errMsg){
		case QLowEnergyController::Error::AuthorizationError: {
			emit onBLEError("Authorization");
			disconnectFromDevice();
			break;
		}
		case QLowEnergyController::Error::ConnectionError: {
			emit onBLEError("Connection");
			disconnectFromDevice();
			break;
		}
		case QLowEnergyController::Error::InvalidBluetoothAdapterError: {
			emit onBLEError("Invalid Bluetooth Adapter");
			disconnectFromDevice();
			break;
		}
		case QLowEnergyController::Error::NetworkError: {
			emit onBLEError("Network");
			disconnectFromDevice();
			break;
		}
		case QLowEnergyController::Error::UnknownError: {
			//emit onBLEError("Unkown");
			break;
		}
		case QLowEnergyController::Error::AdvertisingError: {
			break;
		}
		case QLowEnergyController::Error::RemoteHostClosedError: {
			emit onBLEError("Remote host forcibly closed");
			disconnectFromDevice();
			break;
		}
		case QLowEnergyController::Error::UnknownRemoteDeviceError: {
			//emit onBLEError("Unknown Remote Device");
			break;
		}
		case QLowEnergyController::Error::NoError: {
			break;
		}
	}
}

//Runs on a 35ms timer. See constructor
void DeviceManager::Write()
{
	if(writeBuffer.length() > 0){
		qDebug() << "Writing to serial:" << writeBuffer.at(0);

		//Write characteristic
		bleSerialService->writeCharacteristic(bleSerial, QByteArray::fromStdString(QString(writeBuffer.at(0)).toStdString()),
											  QLowEnergyService::WriteMode::WriteWithoutResponse);
		writeBuffer.remove(0, 1);
	}
}

void DeviceManager::startDiscovery(){
	if(discovering){
		return;
	}
	qDebug() << "Start Discovery";
	//Reset devices
	discoveredDevices.clear();
	deviceMap.clear();
	emit DevicesChanged(devices());

	bleDiscovery->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
	discoveryTimer->stop();
	discoveryTimer->start(10000);
	discovering = true;

	//Alert QML that we are now searching
	emit onStartedSearch();
}

void DeviceManager::stopDiscovery(){
	if(!discovering){
		return;
	}
	qDebug() << "Stop Discovery";
	bleDiscovery->stop();
	discoveryTimer->stop();
	discovering = false;

	//Alert QML that we are no longer searching
	emit onStoppedSearch();
}

void DeviceManager::disconnectFromDevice()
{
	bleController->disconnectFromDevice();
}

void DeviceManager::DiscoverDetails()
{
	bleSerialService->discoverDetails();
}

void DeviceManager::DiscoveredDevice(const QBluetoothDeviceInfo &info)
{
	qDebug() << "Discovered Device:" << info.name();
	discoveredDevices.append(info);
	deviceMap.insert(info.name() + " " + info.address().toString(), info);
	emit DevicesChanged(devices());

	if(info.address().toString() == testDeviceAddress){
		testDevice = info;
	}
}

QStringList DeviceManager::devices()
{
	QStringList val;
	for(int i = 0; i < discoveredDevices.count(); i++){
		val << discoveredDevices[i].name() + " " + discoveredDevices[i].address().toString();
	}

	return val;
}

//===================================================================|
//mainwindow.cpp                                                     |
//===================================================================|
/*
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QIntValidator>
#include <QtMath>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->stackedWidget->setCurrentIndex(0);

	agent = new QBluetoothDeviceDiscoveryAgent();
	connect(agent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &MainWindow::foundDevice);
	agent->start();
	ui->statusLabel->setText("Searching...");

	ui->redEdit->setValidator(new QIntValidator(0, 255, this));
	ui->greenEdit->setValidator(new QIntValidator(0, 255, this));
	ui->blueEdit->setValidator(new QIntValidator(0, 255, this));
	ui->brightnessEdit->setValidator(new QIntValidator(0, 255, this));
	ui->delayEdit->setValidator(new QIntValidator(0, 9999, this));

	QTimer* timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &MainWindow::write);
	timer->start(35);
}

void MainWindow::foundDevice(const QBluetoothDeviceInfo &info){
	if(info.address().toString() == deviceAddress){
		device = info;
		connectToDevice();
		qDebug() << "Found LED controller";
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::sendToWriteBuffer(const QString data)
{
	writeBuffer += data;
}

void MainWindow::write(){
	if(writeBuffer.length() > 0){
		qDebug() << "Before Buffer:" << writeBuffer;
		svc->writeCharacteristic(cmd, QByteArray::fromStdString(QString(writeBuffer.at(0)).toStdString()), QLowEnergyService::WriteMode::WriteWithoutResponse);
		writeBuffer.remove(0, 1);
		qDebug() << "After Buffer:" << writeBuffer;
	}
}

QString MainWindow::convertToWriteable(int num, bool thousand = false)
{
	QString val;

	if(num >= 1000){
		val += QString::number(qFloor(num/1000));
		num -= qFloor(num/1000)*1000;
	} else if(thousand){
		val += "0";
	}

	if(num >= 100){
		val += QString::number(qFloor(num/100));
		num -= qFloor(num/100)*100;
	} else {
		val += "0";
	}

	if(num >= 10){
		val += QString::number(qFloor(num/10));
		num -= qFloor(num/10)*10;
	} else {
		val += "0";
	}

	val += QString::number(num);

	return val;
}

void MainWindow::on_onButton_clicked()
{
	sendToWriteBuffer("W");
}

void MainWindow::on_offButton_clicked()
{
	sendToWriteBuffer("S");
}

void MainWindow::foundDetail(QLowEnergyService::ServiceState newState){
	cmd = svc->characteristic(QBluetoothUuid(charUUID));
	ui->statusLabel->setText("Ready");
	ui->statusLabel->setStyleSheet("color: #00FF00;");
	ui->onButton->setEnabled(true);
	ui->offButton->setEnabled(true);
	ui->colorButton->setEnabled(true);
	ui->palatteButton->setEnabled(true);
}

void MainWindow::foundSvc(const QBluetoothUuid uuid)
{
	qDebug() << "Found svc:" << uuid.toString();
	if(uuid.toString() == "{"+serviceUUID+"}"){
		svc = cont->createServiceObject(QBluetoothUuid(uuid), this);
		connect(svc, &QLowEnergyService::stateChanged, this, &MainWindow::foundDetail);
		svc->discoverDetails();
		qDebug() << "This is desired svc";
	}
}

void MainWindow::connected()
{
	qDebug() << "Connected";
	ui->statusLabel->setText("Connected");
	ui->statusLabel->setStyleSheet("color: #007FFF;");
	cont->discoverServices();
}

void MainWindow::connectToDevice()
{
	ui->statusLabel->setText("Connecting...");
	ui->statusLabel->setStyleSheet("color: #FF9F00;");
	cont = QLowEnergyController::createCentral(device, this);

	connect(cont, &QLowEnergyController::connected, this, &MainWindow::connected);
	connect(cont, &QLowEnergyController::serviceDiscovered, this, &MainWindow::foundSvc);

	cont->setRemoteAddressType(QLowEnergyController::PublicAddress);
	cont->connectToDevice();
}

void MainWindow::on_colorButton_clicked()
{
	ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_backButton_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::updateColorPreview()
{
	ui->colorPreview->setStyleSheet("background-color: rgb("+QString::number(red)+","+QString::number(green)+","+QString::number(blue)+")");
}

void MainWindow::on_redEdit_textEdited(const QString &arg1)
{
	red = arg1.toInt();
	ui->redSlider->setValue(red);
	updateColorPreview();
}

void MainWindow::on_greenEdit_textEdited(const QString &arg1)
{
	green = arg1.toInt();
	ui->greenSlider->setValue(green);
	updateColorPreview();
}

void MainWindow::on_blueEdit_textEdited(const QString &arg1)
{
	blue = arg1.toInt();
	ui->blueSlider->setValue(blue);
	updateColorPreview();
}

void MainWindow::on_redSlider_valueChanged(int value)
{
	red = value;
	ui->redEdit->setText(QString::number(red));
	updateColorPreview();
}

void MainWindow::on_greenSlider_valueChanged(int value)
{
	green = value;
	ui->greenEdit->setText(QString::number(green));
	updateColorPreview();
}

void MainWindow::on_blueSlider_valueChanged(int value)
{
	blue = value;
	ui->blueEdit->setText(QString::number(blue));
	updateColorPreview();
}

void MainWindow::on_brightnessSlider_valueChanged(int value)
{
	bright = value;
	ui->brightnessEdit->setText(QString::number(bright));
}

void MainWindow::on_brightnessEdit_textEdited(const QString &arg1)
{
	bright = arg1.toInt();
	ui->brightnessSlider->setValue(bright);
}

void MainWindow::on_applyButton_clicked()
{
	sendToWriteBuffer("x");
	sendToWriteBuffer("B"+convertToWriteable(bright));
	sendToWriteBuffer("r"+convertToWriteable(red));
	sendToWriteBuffer("g"+convertToWriteable(green));
	sendToWriteBuffer("b"+convertToWriteable(blue));
}

void MainWindow::on_palatteButton_clicked()
{
	ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_backButton_2_clicked()
{
	on_backButton_clicked();
}

void MainWindow::on_paletteApplyButton_clicked()
{
	QString w = "p"+sigmonPalette[ui->paletteBox->currentText()]+sigmonPaletteBlend[ui->blendBox->currentText()];
	sendToWriteBuffer(w);
	sendToWriteBuffer("d"+convertToWriteable(delay, true));
}

void MainWindow::on_delayEdit_textChanged(const QString &arg1)
{
	delay = arg1.toInt();
}

*/