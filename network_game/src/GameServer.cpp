#include "..\\include\\GameServer.h"


Server::Server(){
    if(this->listen(QHostAddress::Any, 1234)){
        qDebug() << "Server is running";
    }
    else{
        qDebug() << "Error when starting the server";
    }
}

void Server::incomingConnection(qintptr socketDescriptor){
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &Server::deleteLater);

    qDebug() << "client is connected " << socketDescriptor;
}

void Server::slotReadyRead(){
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_0);
    if(in.status() == QDataStream::Ok){
        qDebug() << "Read...";
        QString str;
        in >> str;
        qDebug() << str;
    }
    else{
        qDebug() << "Error when receiving message";
    }
}

void Server::sendToClient(QString str){
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out << str;
    socket->write(data);
}
