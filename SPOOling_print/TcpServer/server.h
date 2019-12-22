#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include "tcpclientsocket.h"

class Server : public QTcpServer  //继承自QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent=0,int port=0);

    QList<TcpClientSocket*> tcpClientSocketList;  //保存客户端链接socket
	QList<QString> tcpFilenameList;               //保存客户端文件名

signals:
    void updateServer(QString,QString,int);        //更新服务器，发送文件名和内容
	void input_end(QString);

public slots:
    void updateClients(int,QString,int);
    void slotDisconnected(int);

protected:
    void incomingConnection(int socketDescriptor);  //新建连接
};

#endif // SERVER_H
