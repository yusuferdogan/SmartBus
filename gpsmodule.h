#ifndef GPSMODULE_H
#define GPSMODULE_H

#include <QObject>
#include <QNmeaPositionInfoSource>
#include <QSerialPort>


class GPSModule : public QObject
{
    Q_OBJECT
public:
    explicit GPSModule(QObject *parent = 0);
    QGeoCoordinate* getCurrentCoordinate() { return &currentCoordinate;}

signals:

public slots:
    void positionUpdate(QGeoPositionInfo info);
private:
    QGeoCoordinate currentCoordinate;
};

#endif // GPSMODULE_H
