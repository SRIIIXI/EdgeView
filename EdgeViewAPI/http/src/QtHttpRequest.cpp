
#include "QtHttpRequest.h"
#include "QtHttpHeader.h"
#include "QtHttpServer.h"

QtHttpRequest::QtHttpRequest (QtHttpClientWrapper * client, QtHttpServer * parent)
    : QObject         (parent)
    , _Url           (QUrl ())
    , _Command       (QString ())
    , _Data          (QByteArray ())
    , _ServerReference  (parent)
    , _ClientReference  (client)
{
    // set some additional headers
    addHeader (QtHttpHeader::ContentLength, QByteArrayLiteral ("0"));
    addHeader (QtHttpHeader::Connection,    QByteArrayLiteral ("Keep-Alive"));
}

QUrl QtHttpRequest::getUrl (void) const {
    return _Url;
}

QString QtHttpRequest::getCommand (void) const {
    return _Command;
}

int QtHttpRequest::getRawDataSize (void) const {
    return _Data.size ();
}


QByteArray QtHttpRequest::getRawData (void) const {
    return _Data;
}

QList<QByteArray> QtHttpRequest::getHeadersList (void) const {
    return _HeadersHash.keys ();
}

QtHttpClientWrapper * QtHttpRequest::getClient (void) const {
    return _ClientReference;
}

QByteArray QtHttpRequest::getHeader (const QByteArray & header) const {
    return _HeadersHash.value (header, QByteArray ());
}

void QtHttpRequest::setUrl (const QUrl & url) {
    _Url = url;
}

void QtHttpRequest::setCommand (const QString & command) {
    _Command = command;
}

void QtHttpRequest::addHeader (const QByteArray & header, const QByteArray & value) {
    QByteArray key = header.trimmed ();
    if (!key.isEmpty ()) {
        _HeadersHash.insert (key, value);
    }
}

void QtHttpRequest::appendRawData (const QByteArray & data) {
    _Data.append (data);
}
