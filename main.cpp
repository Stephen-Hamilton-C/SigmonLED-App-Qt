#include "devicemanager.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);

	//DeviceManager dm;

	return app.exec();
}

//===================================================|
//mainwindow.h                                       |
//===================================================|
/*
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
