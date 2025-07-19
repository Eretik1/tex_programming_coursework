#pragma once
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

class Server : public QTcpServer{
    Q_OBJECT

public:
    Server(QObject *parent = nullptr);
    ~Server();
    bool startServer();
    void stopServer();
    void sendToClient(const QString &message);
    QTcpSocket *socket;

private:
    void checkingMessages(const QString &message);

    QVector<QTcpSocket*> sockets;
    QByteArray data;
    quint16 blockSize;


public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();

signals:
    void newConnection();
    void clientDisconnected();
    void closeServer();
    void start();
    void move(const QString &message);
};