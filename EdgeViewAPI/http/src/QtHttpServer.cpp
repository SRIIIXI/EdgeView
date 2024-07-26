
#include "QtHttpServer.hpp"
#include "QtHttpRequest.hpp"
#include "QtHttpReply.hpp"
#include "QtHttpClientWrapper.hpp"

#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>

const QString QtHttpServer::HTTP_VERSION = QStringLiteral ("HTTP/1.1");

QtHttpServer::QtHttpServer (QObject * parent)
    : QObject      (parent)
    , _ServerName (QStringLiteral ("The Qt5 HTTP Server"))
{
    _ServerSocket = new QTcpServer (this);
    connect (_ServerSocket, &QTcpServer::newConnection, this, &QtHttpServer::onClientConnected);
}

const QString & QtHttpServer::getServerName (void) const {
    return _ServerName;
}

quint16 QtHttpServer::getServerPort (void) const {
    return _ServerSocket->serverPort ();
}

QString QtHttpServer::getErrorString (void) const {
    return _ServerSocket->errorString ();
}

void QtHttpServer::start (quint16 port) {
    if (_ServerSocket->listen (QHostAddress::Any, port)) {
        emit started (_ServerSocket->serverPort ());
    }
    else {
        emit error (_ServerSocket->errorString ());
    }
}

void QtHttpServer::stop (void) {
    if (_ServerSocket->isListening ()) {
        _ServerSocket->close ();
        emit stopped ();
    }
}

void QtHttpServer::setServerName (const QString & serverName) {
    _ServerName = serverName;
}

void QtHttpServer::onClientConnected (void) {
    while (_ServerSocket->hasPendingConnections ()) {
        QTcpSocket * sockClient = _ServerSocket->nextPendingConnection ();
        QtHttpClientWrapper * wrapper = new QtHttpClientWrapper (sockClient, this);
        connect (sockClient, &QTcpSocket::disconnected, this, &QtHttpServer::onClientDisconnected);
        _ClientSocketsHash.insert (sockClient, wrapper);
        emit clientConnected (wrapper->getGuid ());
    }
}

void QtHttpServer::onClientDisconnected (void) {
    QTcpSocket * sockClient = qobject_cast<QTcpSocket *> (sender ());
    if (sockClient) {
        QtHttpClientWrapper * wrapper = _ClientSocketsHash.value (sockClient, Q_NULLPTR);
        if (wrapper) {
            emit clientDisconnected (wrapper->getGuid ());
            wrapper->deleteLater ();
            _ClientSocketsHash.remove (sockClient);
        }
    }
}
