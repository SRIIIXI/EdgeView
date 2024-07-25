
#include "QtHttpClientWrapper.h"
#include "QtHttpRequest.h"
#include "QtHttpReply.h"
#include "QtHttpServer.h"
#include "QtHttpHeader.h"

#include <QCryptographicHash>
#include <QTcpSocket>
#include <QStringBuilder>
#include <QStringList>
#include <QDateTime>

const QByteArray & QtHttpClientWrapper::CRLF = QByteArrayLiteral ("\r\n");

QtHttpClientWrapper::QtHttpClientWrapper (QTcpSocket * sock, QtHttpServer * parent)
    : QObject          (parent)
    , _Guid           ("")
    , _ParsingStatus  (AwaitingRequest)
    , _ClientSocket     (sock)
    , _CurrentRequest (Q_NULLPTR)
    , _ServerReference   (parent)
    , _Authenticated (false)
{ 
    connect (_ClientSocket, &QTcpSocket::readyRead, this, &QtHttpClientWrapper::onClientDataReceived);
}

QString QtHttpClientWrapper::getGuid (void)
{
    if (_Guid.isEmpty ())
    {
        _Guid = QString::fromLocal8Bit(QCryptographicHash::hash(QByteArray::number((quint64)(this)), QCryptographicHash::Md5).toHex());
    }

    return _Guid;
}

void QtHttpClientWrapper::onClientDataReceived (void)
{
    if (_ClientSocket != Q_NULLPTR)
    {
        while (_ClientSocket->bytesAvailable ())
        {
            QByteArray line = _ClientSocket->readLine ();

            switch (_ParsingStatus)
            { // handle parsing steps
                case AwaitingRequest:
                { // "command url version" × 1
                        QString str = QString::fromUtf8 (line).trimmed ();
                        QStringList parts = str.split (SPACE, Qt::SkipEmptyParts);

                        if (parts.size () == 3)
                        {
                            QString command = parts.at (0);
                            QString url     = parts.at (1);
                            QString version = parts.at (2);
                            if (version == QtHttpServer::HTTP_VERSION)
                            {
                                //qDebug () << "Debug : HTTP"
                                //          << "command :" << command
                                //          << "url :"     << url
                                //          << "version :" << version;
                                _CurrentRequest = new QtHttpRequest (this, _ServerReference);
                                _CurrentRequest->setUrl     (QUrl (url));
                                _CurrentRequest->setCommand (command);
                                _ParsingStatus = AwaitingHeaders;
                            }
                            else
                            {
                                _ParsingStatus = ParsingError;
                                //qWarning () << "Error : unhandled HTTP version :" << version;
                            }
                        }
                        else
                        {
                            _ParsingStatus = ParsingError;
                            //qWarning () << "Error : incorrect HTTP command line :" << line;
                        }
                        break;
                }
                case AwaitingHeaders:
                { // "header: value" × N (until empty line)
                    QByteArray raw = line.trimmed ();

                    if (!raw.isEmpty ())
                    { // parse headers
                        int pos = raw.indexOf (COLON);

                        if (pos > 0)
                        {
                            QByteArray header = raw.left (pos).trimmed ();
                            QByteArray value  = raw.mid  (pos +1).trimmed ();
                            //qDebug () << "Debug : HTTP"
                            //          << "header :" << header
                            //          << "value :"  << value;
                            _CurrentRequest->addHeader (header, value);

                            if (header == QtHttpHeader::ContentLength)
                            {
                                bool ok  = false;
                                const int len = value.toInt (&ok, 10);

                                if (ok)
                                {
                                    _CurrentRequest->addHeader (QtHttpHeader::ContentLength, QByteArray::number (len));
                                }
                            }
                        }
                        else
                        {
                            _ParsingStatus = ParsingError;
                            qWarning () << "Error : incorrect HTTP headers line :" << line;
                        }
                    }
                    else
                    { // end of headers
                        //qDebug () << "Debug : HTTP end of headers";

                        if (_CurrentRequest->getHeader (QtHttpHeader::ContentLength).toInt () > 0)
                        {
                            _ParsingStatus = AwaitingContent;
                        }
                        else
                        {
                            _ParsingStatus = RequestParsed;
                        }
                    }
                    break;
                }
                case AwaitingContent:
                { // raw data × N (until EOF ??)
                    _CurrentRequest->appendRawData (line);

                    //qDebug () << "Debug : HTTP"
                    //          << "content :" << m_currentRequest->getRawData ().toHex ()
                    //          << "size :"    << m_currentRequest->getRawData ().size  ();

                    if (_CurrentRequest->getRawDataSize () == _CurrentRequest->getHeader (QtHttpHeader::ContentLength).toInt ())
                    {
                        //qDebug () << "Debug : HTTP end of content";
                        _ParsingStatus = RequestParsed;
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }

            switch (_ParsingStatus)
            { // handle parsing status end/error
                case RequestParsed:
                { // a valid request has ben fully parsed
                    QtHttpReply reply (_ServerReference);
                    connect (&reply, &QtHttpReply::requestSendHeaders, this, &QtHttpClientWrapper::onReplySendHeadersRequested);
                    connect (&reply, &QtHttpReply::requestSendData, this, &QtHttpClientWrapper::onReplySendDataRequested);
                    emit _ServerReference->requestNeedsReply (_CurrentRequest, &reply); // allow app to handle request
                    _ParsingStatus = sendReplyToClient (&reply);
                    break;
                }
                case ParsingError:
                { // there was an error durin one of parsing steps
                    _ClientSocket->readAll (); // clear remaining buffer to ignore content
                    QtHttpReply reply (_ServerReference);
                    reply.setStatusCode (QtHttpReply::BadRequest);
                    reply.appendRawData (QByteArrayLiteral ("<h1>Bad Request (HTTP parsing error) !</h1>"));
                    reply.appendRawData (CRLF);
                    _ParsingStatus = sendReplyToClient (&reply);
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }
}

void QtHttpClientWrapper::onReplySendHeadersRequested (void)
{
    QtHttpReply * reply = qobject_cast<QtHttpReply *> (sender ());

    if (reply != Q_NULLPTR)
    {
        QByteArray data;
        // HTTP Version + Status Code + Status Msg
        data.append (QtHttpServer::HTTP_VERSION.toLatin1());
        data.append (SPACE);
        data.append (QByteArray::number (reply->getStatusCode ()));
        data.append (SPACE);
        data.append (QtHttpReply::getStatusTextForCode (reply->getStatusCode ()));
        data.append (CRLF);
        // Header name: header value

        if (reply->useChunked ())
        {
            static const QByteArray & CHUNKED = QByteArrayLiteral ("chunked");
            reply->addHeader (QtHttpHeader::TransferEncoding, CHUNKED);
        }
        else
        {
            reply->addHeader (QtHttpHeader::ContentLength, QByteArray::number (reply->getRawDataSize ()));
        }

        const QList<QByteArray> & headersList = reply->getHeadersList ();

        foreach (const QByteArray & header, headersList)
        {
            data.append (header);
            data.append (COLON);
            data.append (SPACE);
            data.append (reply->getHeader (header));
            data.append (CRLF);
        }
        // empty line
        data.append (CRLF);
        _ClientSocket->write (data);
        _ClientSocket->flush ();
    }
}

void QtHttpClientWrapper::onReplySendDataRequested (void)
{
    QtHttpReply * reply = qobject_cast<QtHttpReply *> (sender ());

    if (reply != Q_NULLPTR)
    {
        // content raw data
        QByteArray data = reply->getRawData ();

        if (reply->useChunked ())
        {
            data.prepend (QByteArray::number (data.size (), 16) % CRLF);
            data.append (CRLF);
            reply->resetRawData ();
        }

        // write to socket
        _ClientSocket->write (data);
        _ClientSocket->flush ();
    }
}

QtHttpClientWrapper::ParsingStatus QtHttpClientWrapper::sendReplyToClient (QtHttpReply * reply)
{
    if (reply != Q_NULLPTR)
    {
        if (!reply->useChunked ())
        {
            reply->appendRawData (CRLF);
            // send all headers and all data in one shot
            reply->requestSendHeaders ();
            reply->requestSendData ();
        }
        else
        {
            // last chunk
            _ClientSocket->write ("0" % CRLF % CRLF);
            _ClientSocket->flush ();
        }

        if (_CurrentRequest != Q_NULLPTR)
        {
            static const QByteArray & CLOSE = QByteArrayLiteral ("close");
            if (_CurrentRequest->getHeader (QtHttpHeader::Connection).toLower () == CLOSE) {
                // must close connection after this request
                _ClientSocket->close ();
            }
            _CurrentRequest->deleteLater ();
            _CurrentRequest = Q_NULLPTR;
        }
    }
    return AwaitingRequest;
}

bool QtHttpClientWrapper::isAuthenticated()
{
    return _Authenticated;
}

void QtHttpClientWrapper::setAuthenticated()
{
    _Authenticated = true;
}

void QtHttpClientWrapper::setUserName(QString &uname)
{
    _UserName = uname;
}

QString QtHttpClientWrapper::getUserName()
{
    return _UserName;
}
