#include "devicemanager.h"
#include "settings.h"

#include <math.h>
#include <QJsonObject>

//Singleton
DeviceManager* DeviceManager::ptrInstance = nullptr;

DeviceManager::DeviceManager(QObject *parent)
{
	//Singleton
	if(ptrInstance != nullptr){
		delete this;
	}
	ptrInstance = this;

	//Initialize discovery agent
	bleDiscovery = new QBluetoothDeviceDiscoveryAgent();
	connect(bleDiscovery, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &DeviceManager::BLEDiscoveredDevice);

	//Initialize write timer
	QTimer* writeTimer = new QTimer(this);
	connect(writeTimer, &QTimer::timeout, this, &DeviceManager::Timer_Write);
	writeTimer->start(15);

	//Initialize stop discovery timer
	discoveryTimer = new QTimer(this);
	connect(discoveryTimer, &QTimer::timeout, this, &DeviceManager::stopDiscovery);

	qDebug() << "DeviceManager constructed";

	//Start searching
	QTimer::singleShot(100, this, &DeviceManager::startDiscovery);
}

DeviceManager::~DeviceManager()
{
	stopDiscovery();
	bleController->disconnectFromDevice();
}

void DeviceManager::QueueWrite(const QString cmd)
{
	writeBuffer += cmd;
	emit writeBufferChanged(writeBuffer);
}

QString DeviceManager::ConvertNumToWritable(int num, const bool hundred)
{
	QString val;

	if(num >= 4095 && hundred)
		return "FFF";

	if(num >= 255 && !hundred)
		return "FF";

	if(num == 0 && hundred)
		return "000";

	if(num == 0 && !hundred)
		return "00";

	int division = num;
	while(division > 0){
		int decimalRemain = division % 16;
		val.insert(0, intToHex(decimalRemain));
		division /= 16;
	}

	if(hundred){
		while(val.length() < 3){
			val.insert(0, '0');
		}
	} else if(val.length() == 1){
		val.insert(0, '0');
	}

	return val;
}

void DeviceManager::ConnectToDevice(const QBluetoothDeviceInfo &device)
{
	//Alert QML that we are connecting
	emit onBLEConnect();
	qDebug() << "Connecting to "+device.name()+"...";

	//Disconnect if already connected
	if(connected){
		disconnectFromDevice();
	}

	//Setup controller
	bleController = QLowEnergyController::createCentral(device, this);
	connect(bleController, &QLowEnergyController::connected, this, &DeviceManager::BLEConnected);

	//Attempt connection
	currentDevice = device;
	bleController->setRemoteAddressType(QLowEnergyController::PublicAddress);
	bleController->connectToDevice();
}

void DeviceManager::BLEConnected(){
	qDebug() << "Connected to "+currentDevice.name();

	//Setup slots
	connect(bleController, &QLowEnergyController::serviceDiscovered, this, &DeviceManager::BLEServiceDiscovered);
	connect(bleController, &QLowEnergyController::disconnected, this, &DeviceManager::BLEDisconnected);

	bleController->discoverServices();

	//Alert QML we are connected
	connected = true;
	emit onBLEConnect();
	emit onBLEConnectedChanged(connected);
}

void DeviceManager::BLEDisconnected()
{
	qDebug() << "Disconnected";

	writeBuffer.clear();
	emit writeBufferChanged(writeBuffer);

	//Alert QML we disconnected
	connected = false;
	ready = false;
	emit onBLEDisconnect();
	emit onBLEConnectedChanged(connected);
	emit onBLEReadyChanged(ready);
}

void DeviceManager::BLEServiceDiscovered(const QBluetoothUuid uuid)
{
	qDebug() << "Service discovered:" << uuid.toString();

	//Check that the service is the serial service
	if(uuid.toString() == serviceUUID){
		qDebug() << "---This is the serial service---";

		//Create service object
		bleSerialService = bleController->createServiceObject(uuid, this);

		//Connect detail discovery slot
		connect(bleSerialService, &QLowEnergyService::stateChanged, this, &DeviceManager::BLEServiceDetailDiscovered);

		//Wait 50 ms and then discover details.
		//Trying to discover details right away causes problems, 50 ms is the most reliable and fast time for discovery.
		QTimer::singleShot(50, this, &DeviceManager::Timer_DiscoverServiceDetails);
	}
}

void DeviceManager::BLEServiceDetailDiscovered(QLowEnergyService::ServiceState newState)
{
	qDebug() << "Detail discovered";
	bleSerial = bleSerialService->characteristic(QBluetoothUuid(charUUID));

	if(bleSerial.isValid()){
		//Alert QML the device is ready to write.
		qDebug() << "Found serial characteristic";

		//Store last connected for auto connection on boot
		settings.setValue("LastConnectedMAC", currentDevice.address().toString());
		shouldReconnect = false;

		//Ensure the Arduino is not locked up by a previously dropped connection
        writeBuffer.clear();
		QueueWrite("x");

		ready = true;
		emit onBLEReady();
		emit onBLEReadyChanged(ready);
	}
}

void DeviceManager::BLEError(QLowEnergyController::Error errMsg)
{
	//Report error messages to UI
	qDebug() << "BLE Error:" << errMsg;
	switch(errMsg){
		case QLowEnergyController::Error::AuthorizationError: {
			emit onBLEFault("Authorization");
			disconnectFromDevice();
			break;
		}
		case QLowEnergyController::Error::ConnectionError: {
			emit onBLEFault("Connection");
			disconnectFromDevice();
			break;
		}
		case QLowEnergyController::Error::InvalidBluetoothAdapterError: {
			emit onBLEFault("Invalid Bluetooth Adapter");
			disconnectFromDevice();
			break;
		}
		case QLowEnergyController::Error::NetworkError: {
			emit onBLEFault("Network");
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
			emit onBLEFault("Remote host forcibly closed");
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
void DeviceManager::Timer_Write()
{
	//Only write if ready and something needs to be written
	if(ready && writeBuffer.length() > 0){
		qDebug() << "Writing to serial:" << writeBuffer.at(0);

		//Write first char in buffer
		bleSerialService->writeCharacteristic(bleSerial,
											  QByteArray::fromStdString(QString(writeBuffer.at(0)).toStdString()),
											  QLowEnergyService::WriteMode::WriteWithoutResponse);

		//Remove first char to move on to next one for next timer loop
		writeBuffer.remove(0, 1);
		emit writeBufferChanged(writeBuffer);
	}
}

void DeviceManager::startDiscovery(){
	if(discovering){
		return;
	}

	qDebug() << "Start Discovery";

	//Reset devices list
	discoveredDevices.clear();
	deviceMap.clear();
	emit DevicesChanged(EncodeDevicesList());

	//Start looking for devices. Stop looking after 10 seconds.
	bleDiscovery->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
	discoveryTimer->stop();
	discoveryTimer->start(10000);

	//Alert QML that we are now searching
	emit onBLEStartedSearch();
	discovering = true;
}

void DeviceManager::stopDiscovery(){
	if(!discovering){
		return;
	}

	qDebug() << "Stop Discovery";

	//Stop searching for devices
	bleDiscovery->stop();
	discoveryTimer->stop();

	//Alert QML that we are no longer searching
	emit onBLEStoppedSearch();
	discovering = false;
}

void DeviceManager::disconnectFromDevice()
{
	bleController->disconnectFromDevice();
}

void DeviceManager::Timer_DiscoverServiceDetails()
{
	bleSerialService->discoverDetails();
}

void DeviceManager::BLEDiscoveredDevice(const QBluetoothDeviceInfo &info)
{
	qDebug() << "Discovered Device:" << info.name();

	//Add device to the list
	discoveredDevices.append(info);
	deviceMap.insert(info.name() + " " + info.address().toString(), info);

	//Alert other backends that the devices list has changed
	emit DevicesChanged(EncodeDevicesList());

	//Assign testDevice if the device is the test device
	if(info.address().toString() == testDeviceAddress){
		testDevice = info;
	}

	if(settings.value("AutoConnect", true).toBool() && shouldReconnect && info.address().toString() == settings.value("LastConnectedMAC").toString()){
		ConnectToDevice(info);
	}
}

QStringList DeviceManager::EncodeDevicesList()
{
	//Loop through each device and add its MAC address to the end for identification
	QStringList val;
	for(int i = 0; i < discoveredDevices.count(); i++){
		val << discoveredDevices[i].name() + " " + discoveredDevices[i].address().toString();
	}

	return val;
}

QChar DeviceManager::intToHex(int num)
{
	switch(num){
		case 0: return '0';
		case 1: return '1';
		case 2: return '2';
		case 3: return '3';
		case 4: return '4';
		case 5: return '5';
		case 6: return '6';
		case 7: return '7';
		case 8: return '8';
		case 9: return '9';
		case 10: return 'A';
		case 11: return 'B';
		case 12: return 'C';
		case 13: return 'D';
		case 14: return 'E';
		case 15: return 'F';
		default: return 0;
	}
}
