#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>

class TcpClientSocket : public QTcpSocket  //�̳���QTcpSocket
{
    Q_OBJECT

public:
    TcpClientSocket(QObject *parent=0);

signals:
    void updateClients(int,QString,int);
    void disconnected(int);
protected slots:
    void dataReceived();
    void slotDisconnected();
};

#endif // TCPCLIENTSOCKET_H
