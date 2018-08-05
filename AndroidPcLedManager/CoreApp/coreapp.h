#ifndef COREAPP_H
#define COREAPP_H

#include <QObject>
#include <QQuickView>
#include <QFile>
#include <QTextStream>
#include <QUrl>
#include <QDir>
#include <QUdpSocket>

#define DBG 0

# define V_MAIN     1
# define V_CREAT    2
# define V_START    3
# define V_END      4

class CoreApp : public QQuickView
{
    Q_OBJECT
public:
    explicit CoreApp(QWindow *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event);
//    void resizeEvent(QResizeEvent* event);
    bool event(QEvent *event) override;


signals:

public slots:
    void    view_changer(int pageid);
    void    load_main();
    void    sendcolor(qreal red, qreal green, qreal blue)
    {
        if (red < 0)
            red = 0;
        if (green < 0)
            green = 0;
        if (blue < 0)
            blue = 0;
        qWarning() << "sendColorParam:" << red << green << blue;

        QByteArray data;

        int value = ((red * 256) - 1);
        if (value > 255)
            value = 255;
        else if (value < 0)
            value = 0;

        data.append('R').append(value);
        value = ((green * 256) - 1);
        if (value > 255)
            value = 255;
        else if (value < 0)
            value = 0;
        data.append('G').append(value);

        value = ((blue * 256) - 1);

        if (value > 255)
            value = 255;
        else if (value < 0)
            value = 0;
        data.append('B').append(value);
        m_socket->writeDatagram(data,QHostAddress::Broadcast,4242);

    }

    void    sendLightIntensity(qreal light)
    {
        if (light < 0)
            light = 0;

        QByteArray data;

        int value = ((light * 256) - 1);
        if (value > 255)
            value = 0;
        else if (value < 0)
            value = 1;

        data.append('L').append(value);
        m_socket->writeDatagram(data,QHostAddress::Broadcast,4242);

    }

private:
    int             m_pageid;
    QUdpSocket      *m_socket;

};



#endif // COREAPP_H

