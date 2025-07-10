#pragma once
#include <QTcpSocket>
#include <QObject>
#include <QDebug>

class Client : public QObject {
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    bool connectToServer(const QString &ip, quint16 port);

public slots:
    void sendMessage(const QString &message);
    void readyRead();
    void disconnected();

private:
    QTcpSocket *m_socket;
};
