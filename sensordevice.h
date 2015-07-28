#ifndef SENSORDEVICE_H
#define SENSORDEVICE_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

#include "iris/dist500/Dist500.h"
#include "iris/drivers/DriverManager.h"
#include "gpsmodule.h"

using namespace iris::dist500;
using namespace iris::drivers;
using namespace iris::uip;
using namespace std;

enum doorState {
    opened = 0x64,
    closed = 0x00
};

class SensorDevice : public QThread
{
    Q_OBJECT
public:
    SensorDevice(string url, string host, int port, QObject *parent = 0);

    void setDoorState(doorState state);
    doorState getDoorState();

    bool getSensorState();
    void getCountResult(int& alight, int& board);
    void sendToServer(QGeoCoordinate* location, int alig, int board, int celc);

private:
    Dist500* d5;
    string deviceURL;
    unsigned short functionArea;
    unsigned short doorNumber;
    bool isCounting;
    GPSModule *gpsModule;
    QGeoCoordinate* location;
    QTcpSocket* pSocket;

signals:
    void doorOpen();
    void doorClose();

protected slots:
    void stopCounting();
    void startCouting();

protected:
    void run();
};

#endif // SENSORDEVICE_H
