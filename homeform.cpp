#include "homeform.h"
#include "devicemanager.h"

#include <QStandardItemModel>

HomeForm::HomeForm(QObject *parent) : QObject(parent)
{
	connect(DeviceManager::getInstance(), &DeviceManager::DevicesChanged, this, &HomeForm::devicesUpdated);
}

void HomeForm::connectPressed()
{
	DeviceManager* dm = DeviceManager::getInstance();
	if(!dm->connected){
		if(highlightedDelegate.length() > 0){

			QBluetoothDeviceInfo info = dm->deviceMap[highlightedDelegate];
			dm->ConnectToDevice(info);
		}
	} else {
		dm->disconnectFromDevice();
	}
}

void HomeForm::connectToTestDevice()
{
	DeviceManager::getInstance()->ConnectToDevice(DeviceManager::getInstance()->testDevice);
}

bool HomeForm::showAll()
{
	return m_showAll;
}

void HomeForm::setShowAll(bool showAll)
{
	m_showAll = showAll;
	devicesUpdated(DeviceManager::getInstance()->deviceMap.keys());
}

void HomeForm::devicesUpdated(QStringList deviceNames)
{
	if(m_showAll){
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
			if(deviceBrand == shownBrand){
				devices << device;
			}
		}
	}

	emit devicesChanged(devices);
}
