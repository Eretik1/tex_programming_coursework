#pragma once
#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QDebug>

class Server : public QTcpServer{
    Q_OBJECT

public:
    Server();
    void sendToClient(QString str);

    QTcpSocket *socket;

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();

private:
    QByteArray data;

};