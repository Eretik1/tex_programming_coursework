#pragma once
#include <QTcpSocket>
#include <QObject>
#include <QDebug>

class Client : public QObject {
    Q_OBJECT

public:
    Client(QObject *parent = nullptr);
    ~Client();
    void disconnectToServer();
    bool connectToServer(const QString &ip, quint16 port);
    void sendToServer(const QString &message);
    quint16 blockSize;

public slots:
    void slotReadyRead();

private:
    void checkingMessages(const QString &message);

    QByteArray data;
    QTcpSocket *socket;

signals:
    void disconnect();
    void start();
    void move(const QString &message);
};