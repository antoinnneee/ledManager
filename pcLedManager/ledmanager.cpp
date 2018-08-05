#include "ledmanager.h"
#include <QSerialPortInfo>
#include <QUdpSocket>
#include <QList>
#include <QTimer>

LedManager::LedManager(QObject *parent) : QObject(parent)
{
    QList<QSerialPortInfo> infoList =  QSerialPortInfo::availablePorts();

    m_serial = new QSerialPort();
    if (!infoList.isEmpty())
        m_serial->setPort(infoList.last());
    m_serial->setBaudRate(115200);
    m_serial->open(QIODevice::ReadWrite);
    m_serialSendTimer = new QTimer(this);
    m_serialSendTimer->setInterval(150);
    connect(m_serialSendTimer, SIGNAL(timeout()), this, SLOT(sendSerialData()));
    m_serialSendTimer->start();
    ledColor[0] = 0;
    ledColor[1] = 0;
    ledColor[2] = 0;
    setColor();
    m_socket = new QUdpSocket();
    m_socket->bind(4242, QUdpSocket::ShareAddress);
    connect(this, SIGNAL(dataReceived(QByteArray)), this, SLOT(processData(QByteArray)));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(hasPendingDatagram()));
    connect(m_serial, SIGNAL(readyRead()), this, SLOT(hasPendingSerial()));
    connect(this, SIGNAL(dataUpdated()), this, SLOT(setColor()));
}

void    LedManager::processData(QByteArray data)
{
    int i = 0;
    while(i < data.length())
    {
        if (data.at(i) == 'R' || data.at(i) == 'G' || data.at(i) == 'B' || data.at(i) == 'L')
        {
            if (data.at(i) == 'R')
            {
                i++;
                ledColor[0] = data.at(i);
            }
            else if (data.at(i) == 'G')
            {
                i++;
                ledColor[1] = data.at(i);
            }
            else if (data.at(i) == 'B')
            {
                i++;
                ledColor[2] = data.at(i);
            }
            else if (data.at(i) == 'L')
            {
                i++;
                lightIntensity = 256 - data.at(i);
            }
        }
        i++;
    }
    emit dataUpdated();
}



