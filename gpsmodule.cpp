#include "gpsmodule.h"
#include <QGeoPositionInfoSource>
#include <QDebug>
#include <QGeoCircle>

GPSModule::GPSModule(QObject *parent) : QObject(parent)
{
    QSerialPort* serial = new QSerialPort(this);
    serial->setPortName(QString("/dev/ttyUSB0"));
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->open(QIODevice::ReadOnly);

    if(serial->isOpen())
    {
        QNmeaPositionInfoSource *source = new QNmeaPositionInfoSource(QNmeaPositionInfoSource::RealTimeMode);
        source->setDevice(serial);

        if(source){
            connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(positionUpdate(QGeoPositionInfo)));
            source->setPreferredPositioningMethods(QGeoPositionInfoSource::AllPositioningMethods);
            source->setUpdateInterval(2000);
            source->startUpdates();
        }
    }
}

void GPSModule::positionUpdate(QGeoPositionInfo info)
{
    currentCoordinate = info.coordinate();
    // TO DO ..
}

