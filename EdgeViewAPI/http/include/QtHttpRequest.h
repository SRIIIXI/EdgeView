#ifndef QTHTTPREQUEST_H
#define QTHTTPREQUEST_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QHash>
#include <QUrl>

class QtHttpServer;
class QtHttpClientWrapper;

class QtHttpRequest : public QObject
{
    Q_OBJECT
public:
    explicit QtHttpRequest (QtHttpClientWrapper * client, QtHttpServer * parent);
    int                   getRawDataSize (void) const;
    QUrl                  getUrl         (void) const;
    QString               getCommand     (void) const;
    QByteArray            getRawData     (void) const;
    QList<QByteArray>     getHeadersList (void) const;
    QtHttpClientWrapper * getClient      (void) const;
    QByteArray getHeader (const QByteArray & header) const;
public slots:
    void setUrl        (const QUrl & url);
    void setCommand    (const QString & command);
    void addHeader     (const QByteArray & header, const QByteArray & value);
    void appendRawData (const QByteArray & data);
private:
    QUrl                          _Url;
    QString                       _Command;
    QByteArray                    _Data;
    QtHttpServer *                _ServerReference;
    QtHttpClientWrapper *         _ClientReference;
    QHash<QByteArray, QByteArray> _HeadersHash;
};

#endif
