#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QIntValidator>
#include <QtMath>

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

void MainWindow::write(const QString data)
{
	svc->writeCharacteristic(cmd, QByteArray::fromStdString(data.toStdString()), QLowEnergyService::WriteMode::WriteWithoutResponse);
}

QString MainWindow::convertToWriteable(int num, bool thousand = false)
{
	QString val;

	qDebug() << "num:" << num << "val:" << val;

	if(num >= 1000){
		val += QString::number(qFloor(num/1000));
		num -= qFloor(num/1000)*1000;
	} else if(thousand){
		val += "0";
	}

	qDebug() << "num:" << num << "val:" << val;

	if(num >= 100){
		val += QString::number(qFloor(num/100));
		num -= qFloor(num/100)*100;
	} else {
		val += "0";
	}

	qDebug() << "num:" << num << "val:" << val;

	if(num >= 10){
		val += QString::number(qFloor(num/10));
		num -= qFloor(num/10)*10;
	} else {
		val += "0";
	}

	qDebug() << "num:" << num << "val:" << val;

	val += QString::number(num);

	qDebug() << "num:" << num << "val:" << val;

	return val;
}

void MainWindow::on_onButton_clicked()
{
	write("W");
}

void MainWindow::on_offButton_clicked()
{
	write("S");
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
	qDebug() << "background-color: rgb("+QString::number(red)+","+QString::number(green)+","+QString::number(blue)+")";
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
	write("B"+convertToWriteable(bright));
	write("r"+convertToWriteable(red));
	write("g"+convertToWriteable(green));
	write("b"+convertToWriteable(blue));
}

void MainWindow::on_palatteButton_clicked()
{
	ui->stackedWidget->setCurrentIndex(2);
}
