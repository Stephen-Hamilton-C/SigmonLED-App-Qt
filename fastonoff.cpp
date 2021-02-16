#include "fastonoff.h"
#include "devicemanager.h"

FastOnOff::FastOnOff(QObject *parent) : QObject(parent)
{

}

void FastOnOff::on()
{
	//Wake
	DeviceManager::getInstance()->QueueWrite("W");
}

void FastOnOff::off()
{
	//Sleep
	DeviceManager::getInstance()->QueueWrite("S");
}
