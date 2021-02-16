#include "homeform.h"
#include "devicemanager.h"

HomeForm::HomeForm(QObject *parent) : QObject(parent)
{
	connect(DeviceManager::getInstance(), &DeviceManager::DevicesChanged, this, &HomeForm::DeviceListUpdated);
}

void HomeForm::connectPressed()
{
	DeviceManager* dm = DeviceManager::getInstance();
	if(!dm->connected){
		//Get selected device from the currently highlighted item in the list.
		if(highlightedDelegate.length() > 0){
			//The delegate is encoded with the MAC address. Luckily, I'm smart, and made it really easy to map it to a device.
			QBluetoothDeviceInfo info = dm->deviceMap[highlightedDelegate];
			dm->ConnectToDevice(info);
		}
	} else {
		//Act as a disconnect button if connect
		dm->disconnectFromDevice();
	}
}

void HomeForm::connectToTestDevice()
{
	DeviceManager::getInstance()->ConnectToDevice(DeviceManager::getInstance()->testDevice);
}

bool HomeForm::showAll()
{
	return m_ShowAll;
}

void HomeForm::setShowAll(bool showAll)
{
	m_ShowAll = showAll;

	//Update the device list with *all* the discovered devices
	DeviceListUpdated(DeviceManager::getInstance()->deviceMap.keys());
}

void HomeForm::DeviceListUpdated(QStringList deviceNames)
{
	if(m_ShowAll){
		devices = deviceNames;
	} else {
		devices = QStringList();
		for(int i = 0; i < deviceNames.count(); i++){
			const QString device = deviceNames[i];
			qDebug() << "Device:" << device;
			QString deviceBrand = device.right(17);
			qDebug() << "DeviceMAC:" << deviceBrand;
			deviceBrand = deviceBrand.left(8);
			qDebug() << "DeviceBrand:" << deviceBrand;
			if(deviceBrand == idMACType){
				devices << device;
			}
		}
	}

	emit devicesChanged(devices);
}
