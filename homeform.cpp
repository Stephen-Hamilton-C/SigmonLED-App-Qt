#include "homeform.h"
#include "devicemanager.h"

HomeForm::HomeForm(QObject *parent) : QObject(parent)
{

}

void HomeForm::connectToTestDevice()
{
	DeviceManager::getInstance()->ConnectToDevice(DeviceManager::getInstance()->testDevice);
}
