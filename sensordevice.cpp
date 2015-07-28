#include "sensordevice.h"

#include <iostream>

SensorDevice::SensorDevice(string url, string host, int port, QObject* parent)
    :deviceURL(url), isCounting(false), functionArea(1), doorNumber(1), QThread(parent)
{
    DriverManager& dm = DriverManager::getInstance();
    dm.createAndActivateDefaultDrivers();
    Sensor& s = dm.getSensorFor(url);
    d5 = new Dist500(s);
    gpsModule = new GPSModule();
    pSocket = new QTcpSocket(this);
    pSocket->connectToHost(QString::fromStdString(host), port);

    connect(this, SIGNAL(doorOpen()), this, SLOT(startCouting()));
    connect(this, SIGNAL(doorClose()), this, SLOT(stopCounting()));
}

void SensorDevice::setDoorState(doorState state)
{
    if(!d5)
    {
        d5->setDoorState(functionArea, doorNumber, state, state);
    }
}

doorState SensorDevice::getDoorState()
{
    unsigned char left = 0, right = 0;

    if(!d5)
    {
        d5->getDoorState(functionArea, doorNumber, left, right);

        if(!left && !right)
            return opened;
        else
            return closed;
    }
}

void SensorDevice::stopCounting()
{
    if(isCounting){
        int al, bol;

        //qDebug() << "Sayma sonlanıyor..\n";
        setDoorState(closed);
        d5->stopCounting();
        getCountResult(al, bol);
        isCounting = false;

        sendToServer(location, al, bol, 20);
    }
}


void SensorDevice::startCouting()
{
    if(isCounting){
        setDoorState(opened);
        d5->startCounting();
        isCounting = true;
        location  = (gpsModule->getCurrentCoordinate());
    }
}

bool SensorDevice::getSensorState(){
    return isCounting;
}

void SensorDevice::getCountResult(int &alight, int &board)
{
    Dist500::CountList cl;

        d5->getCountResults(functionArea, current_counter, false, 0xff, cl);
        Dist500::FunctionAreaStatusList sl;
        d5->getFunctionAreaStatuses(sl);
        bool buffered = false;

        for(Dist500::FunctionAreaStatusList::const_iterator i = sl.begin(); i != sl.end(); ++i)
        {
            functionAreaStatus stat = *i;
            if(stat.functionAreaNumber == functionArea && stat.functionAreaStatusBytes == new_counting_result)
                buffered = true;
        }

        if(buffered){
            cl.clear();
            d5->getCountResults(functionArea, buffer_counter, false, 0xff, cl);

        }

        for(Dist500::CountList::const_iterator k = cl.begin(); k != cl.end(); ++k){
            category_counts cnt = *k;
            alight = cnt.alighting;
            board = cnt.boarding;
        }
}

void SensorDevice::run()
{
    char result;

    forever {
        std::cin >> result;

        if(result == 'o' || result == 'O')
        {
            emit doorOpen();
        }
        else if(result == 'c' || result == 'C' )
        {
           emit doorClose();
        }
        else if(result == 'q' || result == 'Q')
        {
            exit(1);
        }
        else
            continue;
    }
}

void SensorDevice::sendToServer(QGeoCoordinate *location, int alig, int board, int celc)
{
    QString cornerNo("C11M6");
    double x = location->latitude();
    double y = location->longitude();

    QString str = QString("%1_%2_%3_%4_%5_%6_%7_%8_%9_%10").arg(cornerNo).arg(doorNumber).arg(board).arg(alig).arg((board - alig)).arg(25).arg(80)
               .arg(x).arg(y).arg(QDateTime::currentDateTime().toString());

     pSocket->write(str.toStdString().c_str());
}






















