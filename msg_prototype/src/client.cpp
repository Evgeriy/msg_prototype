#include "client.h"

#include <QDebug>
#include <QtWebSockets/QWebSocket>
#include <iostream>

using namespace nlohmann;

TCPClient::TCPClient(QObject *_parent) :
    QObject(_parent),
    pSocket(nullptr),
    mNextBlockSize(0) {

}

TCPClient::~TCPClient() {
    if (pSocket != nullptr) {
        delete pSocket;
        pSocket = nullptr;
    }
}

void TCPClient::connectToHost(const QString &_hostAddressString, const quint16 &_port) {
    pSocket = new QTcpSocket(this);
    pSocket->connectToHost(_hostAddressString, _port);

    connect(pSocket, &QTcpSocket::connected, this, &TCPClient::onConnected);
    connect(pSocket, &QTcpSocket::disconnected, this, &TCPClient::closed);
    connect(pSocket, &QTcpSocket::readyRead, this, &TCPClient::onMessageReceived);
}

void TCPClient::sendAuthorizationData() {
    // create json
    json jsonAuthData;
    jsonAuthData["phoneNumber"] = m_phoneNumber.toStdString();
    jsonAuthData["code"] = 0;

    // pack json to std::string
    std::string packedStdString = "";
    json::to_msgpack(jsonAuthData, packedStdString);
    packedStdString = "0000" + packedStdString;

    // write packed json to socket
    pSocket->write(packedStdString.c_str(), packedStdString.size());
}

void TCPClient::sendUserNikname(const QString &_userNikName) {

}

QString TCPClient::getPhoneNumber() const {
    return m_phoneNumber;
}

QString TCPClient::getNikName() const {
    return m_nikName;
}

QString TCPClient::getFirstName() const {
    return m_firstName;
}

QString TCPClient::getSecondName() const {
    return m_secondName;
}

QString TCPClient::getCode() const {
    return m_code;
}

QStringList TCPClient::getFriends() const {
    return m_friends;
}

QStringList TCPClient::getMessages() const {
    return m_messages;
}

void TCPClient::setPhoneNumber(const QString &_phoneNumber) {
    m_phoneNumber = _phoneNumber;
}

void TCPClient::setNikName(const QString &_nikName) {
    m_nikName = _nikName;
}

void TCPClient::setFirstName(const QString &_firstName) {
    m_firstName = _firstName;
}

void TCPClient::setSecondName(const QString &_secondName) {
    m_secondName = _secondName;
}

void TCPClient::setCode(const QString &_code) {
    m_code = _code;
}

void TCPClient::setFriends(const QStringList &_friends) {
    m_friends = _friends;
}

void TCPClient::setMessages(const QStringList &_messages) {
    m_messages = _messages;
}

void TCPClient::onConnected() {
    qDebug() << "Client IP:" << pSocket->localAddress().toString() <<
                "Server IP:" << pSocket->peerAddress().toString();

    QByteArray array;
    array.append(QString("0000"));
//    array.append(CBOR::pack("hello from client"));

    //pSocket->write(array);
}

void TCPClient::onMessageReceived() {
    QDataStream inputDataStream(pSocket);
    inputDataStream.setVersion(QDataStream::Qt_5_11);

    qDebug() << pSocket->readAll();

//    while (true) {
//        if (!mNextBlockSize) {
//            qDebug() << pSocket->bytesAvailable();
//            if (pSocket->bytesAvailable() < sizeof(qint16)) {
//                break;
//            }
//            inputDataStream >> mNextBlockSize;
//            qDebug() << mNextBlockSize;
//        }

//        if (pSocket->bytesAvailable() < mNextBlockSize) {
//            break;
//        }

//        qDebug() << mNextBlockSize;
//        qDebug() << pSocket->readAll();

//        mNextBlockSize = 0;

//        std::string readedAll = pSocket->readAll().toStdString();
//        qDebug() << QString::fromStdString(readedAll);
//    }
}
