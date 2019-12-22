#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include "tcpclientsocket.h"

class Server : public QTcpServer  //�̳���QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent=0,int port=0);

    QList<TcpClientSocket*> tcpClientSocketList;  //����ͻ�������socket
	QList<QString> tcpFilenameList;               //����ͻ����ļ���

signals:
    void updateServer(QString,QString,int);        //���·������������ļ���������
	void input_end(QString);

public slots:
    void updateClients(int,QString,int);
    void slotDisconnected(int);

protected:
    void incomingConnection(int socketDescriptor);  //�½�����
};

#endif // SERVER_H
