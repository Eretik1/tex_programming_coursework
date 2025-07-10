#pragma once
#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QDebug>

class Server : public QObject {
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    bool start(quint16 port);
    void sendMessage(const QString &message);

private slots:
    void newConnection();
    void readyRead();
    void disconnected();

private:
    QTcpServer *m_server;
    QList<QTcpSocket*> m_clients;
};
