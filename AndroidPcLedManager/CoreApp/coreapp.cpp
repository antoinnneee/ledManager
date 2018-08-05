#include "coreapp.h"

#include <QWindow>
#include <QQmlContext>
#include <QSettings>
#include <QVariant>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QUrl>
#include <QDir>

/*
 * QQuickView derived class
 */

CoreApp::CoreApp(QWindow *parent) : QQuickView(parent)
{
    setResizeMode(QQuickView::SizeRootObjectToView);

    m_socket = new QUdpSocket(this);
    m_socket->bind(4242,QUdpSocket::ShareAddress);
//    m_socket->open(QIODevice::ReadWrite);
    view_changer(V_MAIN);
}

void CoreApp::view_changer(int pageid)
{
    if (pageid == V_MAIN)
        QMetaObject::invokeMethod(this, "load_main", Qt::QueuedConnection);
}


void CoreApp::load_main()
{

    setSource(QUrl("qrc:/Main.qml"));
    QObject *object = (QObject*) rootObject();
    connect(object, SIGNAL(colorUpdated(qreal, qreal, qreal)), this, SLOT(sendcolor(qreal, qreal, qreal)));
    connect(object, SIGNAL(lightIntensityUpdated(qreal)), this, SLOT(sendLightIntensity(qreal)));
//    m_anchor = object->findChild<QObject*>("anchor");
    m_pageid = V_MAIN;
}


/*
 * Gestion Close Event
 */
bool CoreApp::event(QEvent *event)
 {
     if (event->type() == QEvent::Close)
     {

     }
     return QQuickView::event(event);
 }

