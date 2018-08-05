#ifndef LEDMANAGER_H
#define LEDMANAGER_H

#include <QObject>
#include <QString>
#include <QUdpSocket>
#include <QDebug>
#include <QTimer>

#include <QtSerialPort/QSerialPort>
class LedManager : public QObject
{
    Q_OBJECT
public:
    explicit LedManager(QObject *parent = nullptr);

signals:
    void    dataReceived(QByteArray);
    void    dataUpdated();

public slots:
    void    sendSerialData()
    {
        if (!m_serialSendBuffer.isEmpty())
        {
            m_serial->write(m_serialSendBuffer);
            m_serialSendBuffer.clear();

        }
    }

    void    hasPendingDatagram()
    {
        QByteArray data;
        while(m_socket->hasPendingDatagrams())
        {
            data.resize(int(m_socket->pendingDatagramSize()));
            m_socket->readDatagram(data.data(), data.size());
            emit dataReceived(data);
//            qWarning() << data;
        }
    }

    void    hasPendingSerial()
    {
        QByteArray data;
        data = m_serial->readAll();
        qWarning() << data;
    }

    void    processData(QByteArray data);
    void setColor(){
        QByteArray com("R");
        com.append((char)ledColor[0]).append('G').append((char)ledColor[1]).append('B').append((char)ledColor[2]);
        com.append('L').append(lightIntensity);
        m_serialSendBuffer = com;

    }

    void setColor(unsigned char R, unsigned char G, unsigned char B)
    {
        ledColor[0] = R;
        ledColor[1] = G;
        ledColor[2] = B;
        QByteArray com("R");
        com.append((char)ledColor[0]).append('G').append((char)ledColor[1]).append('B').append((char)ledColor[2]);
        m_serialSendBuffer = com;
    }

    void setLight(unsigned char light)
    {
        QByteArray com("L");
        com.append(light);
        m_serialSendBuffer = com;
    }

    int    getRed() { return ledColor[0]; }
    int    getGreen() { return ledColor[1]; }
    int    getBlue() { return ledColor[2]; }
    int    getLightIntensity() { return lightIntensity; }

private:
    unsigned char ledColor[3];
    unsigned char lightIntensity;
    QSerialPort     *m_serial;
    QTimer          *m_serialSendTimer;
    QUdpSocket      *m_socket;
    QByteArray      m_serialSendBuffer;

};

#endif // LEDMANAGER_H
