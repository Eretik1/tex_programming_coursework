#pragma once
#include <QTcpSocket>
#include <QObject>
#include <QDebug>

class Client : public QObject {
    Q_OBJECT

public:
    Client(QObject *parent = nullptr);
    ~Client();
    bool connectToServer(const QString &ip, quint16 port);
    void sendToServer(const QString &message);
    void disconnectFromHost();
    quint16 blockSize;

public slots:
    void slotReadyRead();

private:
    QByteArray data;
    QTcpSocket *socket;

signals:
    void disconnect();
};
