#include "..\\include\\GameServer.h"

Server::Server(QObject *parent) : QTcpServer(parent){
    qDebug() << "server created";
    blockSize = 0;
}

Server::~Server(){
    qDebug() << "server deleted";
}

bool Server::startServer(){
    if (listen(QHostAddress::Any, 12345)) {
        qDebug() << "The server is running on port" << 12345;
        return true;
    }
    qDebug() << "Server startup error:" << errorString();
    return false;
}

void Server::incomingConnection(qintptr socketDescriptor){
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    sockets.append(socket);
    
    emit newConnection();

    qDebug() << "New connection from" << socketDescriptor;
}

void Server::slotReadyRead(){
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    if(in.status() == QDataStream::Ok){
        qDebug() << "Read...";
        while(true){
            if(blockSize == 0){
                if(socket->bytesAvailable() < 2){
                    break;
                }
                in >> blockSize;
            }
            if(socket->bytesAvailable() < blockSize){
                break;
            }
            QString str;
            in >> str;
            blockSize = 0;
            qDebug() << str;
            break;
        }
        QString massege = "Hello";
        this->sendToClient(massege);
    }
    else{
        qDebug() << "error reading message";
    }
}

void Server::sendToClient(const QString &message) {
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out << quint16(0) << message;
    out.device()->seek(0);
    out << quint16(data.size() - sizeof(quint16));
    socket->write(data);
    qDebug() << "message sent";
}

void Server::stopServer(){
    if(sockets.size() != 0){
        socket->disconnectFromHost();
    }
    sockets.clear();
    this->close();
    emit closeServer();
    qDebug() << "close server";
};
