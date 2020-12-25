#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	agent = new QBluetoothDeviceDiscoveryAgent();
	connect(agent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &MainWindow::foundDevice);
	agent->start();
}

void MainWindow::foundDevice(const QBluetoothDeviceInfo &info){
	qDebug() << "Found one";
	if(info.address().toString() == deviceAddress){
		device = info;
		connectToDevice();
		qDebug() << "Found it!";
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::on_onButton_clicked()
{
	svc->writeCharacteristic(cmd, QByteArray::fromStdString("W"), QLowEnergyService::WriteMode::WriteWithoutResponse);
}

void MainWindow::on_offButton_clicked()
{
	svc->writeCharacteristic(cmd, QByteArray::fromStdString("S"), QLowEnergyService::WriteMode::WriteWithoutResponse);
}

void MainWindow::foundDetail(QLowEnergyService::ServiceState newState){
	cmd = svc->characteristic(QBluetoothUuid(charUUID));
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
	cont->discoverServices();
}

void MainWindow::connectToDevice()
{
	cont = QLowEnergyController::createCentral(device, this);

	connect(cont, &QLowEnergyController::connected, this, &MainWindow::connected);
	connect(cont, &QLowEnergyController::serviceDiscovered, this, &MainWindow::foundSvc);

	cont->setRemoteAddressType(QLowEnergyController::PublicAddress);
	cont->connectToDevice();
}


