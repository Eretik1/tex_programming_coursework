#include "..\\include\\GameClient.h"

Client::Client(QObject *parent) : QObject(parent) {
    qDebug() << "client created";
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &Client::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    connect(socket, &QTcpSocket::disconnected, this, [this](){
        this->disconnectToServer();
    });
    blockSize = 0;
}

Client::~Client(){
    qDebug() << "client deleted";
}

bool Client::connectToServer(const QString &ip, quint16 port) {
    socket->connectToHost(ip, port);
    if (!socket->waitForConnected(5000)) {
        qDebug() << "Connection failed";
        return false;
    }
    qDebug() << "Connected to server at" << ip << ":" << port;
    return true;
}

void Client::slotReadyRead() {
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
            this->checkingMessages(str);
            break;
        }
    }
    else{
        qDebug() << "Error when receiving message";
    }
}

void Client::sendToServer(const QString &message) {
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out << quint16(0) << message;
    out.device()->seek(0);
    out << quint16(data.size() - sizeof(quint16));
    socket->write(data);
    qDebug() << "message sent";
}

void Client::disconnectToServer(){
    if (socket && socket->state() == QAbstractSocket::ConnectedState) {
        socket->disconnectFromHost();  
        if (socket->state() != QAbstractSocket::UnconnectedState) {
            socket->waitForDisconnected(1000);
        }
    }
    emit disconnect();
    qDebug() << "disconnect from the server";
}

void Client::checkingMessages(const QString &message){
    if(message.indexOf("START") != -1){
        emit start(message);
    }
    if(message.indexOf("MOVE") != -1){
        emit move(message);
    }
    if(message.indexOf("COLOR") != -1){
        emit setColor(message);
    }
    if(message.indexOf("SURRENDERED") != -1){
        emit gameOver(message);
    }
}