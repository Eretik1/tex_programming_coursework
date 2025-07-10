#include "..\\include\\GameClient.h"
Client::Client(QObject *parent) : QObject(parent), m_socket(new QTcpSocket(this)) {
    connect(m_socket, &QTcpSocket::readyRead, this, &Client::readyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &Client::disconnected);
}

bool Client::connectToServer(const QString &ip, quint16 port) {
    m_socket->connectToHost(ip, port);
    if (!m_socket->waitForConnected(5000)) {
        qDebug() << "Connection failed:" << m_socket->errorString();
        return false;
    }
    qDebug() << "Connected to server at" << ip << ":" << port;
    return true;
}

void Client::readyRead() {
    QByteArray data = m_socket->readAll();
    QString message = QString::fromUtf8(data);
    qDebug() << "Message from server:" << message;
}

void Client::disconnected() {
    qDebug() << "Disconnected from server";
}

void Client::sendMessage(const QString &message) {
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        m_socket->write(message.toUtf8());
    }
}