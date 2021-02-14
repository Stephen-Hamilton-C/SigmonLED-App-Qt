#include "fastonoff.h"
#include "devicemanager.h"

FastOnOff::FastOnOff(QObject *parent) : QObject(parent)
{

}

void FastOnOff::on()
{
	DeviceManager::getInstance()->QueryWrite("W");
}

void FastOnOff::off()
{
	DeviceManager::getInstance()->QueryWrite("S");
}
