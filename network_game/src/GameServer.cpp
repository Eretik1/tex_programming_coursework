#include "..\\include\\GameServer.h"
Server::Server(QObject *parent) : QObject(parent), m_server(new QTcpServer(this)) {
    connect(m_server, &QTcpServer::newConnection, this, &Server::newConnection);
}

bool Server::start(quint16 port) {
    if (!m_server->listen(QHostAddress::Any, port)) {
        qDebug() << "Server could not start:" << m_server->errorString();
        return false;
    }
    qDebug() << "Server started on port" << port;
    return true;
}

void Server::newConnection() {
    QTcpSocket *socket = m_server->nextPendingConnection();
    m_clients.append(socket);
    connect(socket, &QTcpSocket::readyRead, this, &Server::readyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Server::disconnected);
    qDebug() << "New client connected:" << socket->peerAddress().toString();
}

void Server::readyRead() {
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    QByteArray data = socket->readAll();
    QString message = QString::fromUtf8(data);
    qDebug() << "Received:" << message;

    // Broadcast to all clients
    for (QTcpSocket *client : m_clients) {
        if (client != socket) {
            client->write(data);
        }
    }
}

void Server::disconnected() {
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    m_clients.removeAll(socket);
    socket->deleteLater();
    qDebug() << "Client disconnected";
}

void Server::sendMessage(const QString &message) {
    for (QTcpSocket *client : m_clients) {
        client->write(message.toUtf8());
    }
}