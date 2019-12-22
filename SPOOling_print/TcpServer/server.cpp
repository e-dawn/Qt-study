#include "server.h"

Server::Server(QObject *parent,int port)
    :QTcpServer(parent)
{
    listen(QHostAddress::Any,port);  //��port�˿ڶ������ַ���� P344
}

void Server::incomingConnection(int socketDescriptor)  //����������
{
    TcpClientSocket *tcpClientSocket=new TcpClientSocket(this);
    connect(tcpClientSocket,SIGNAL(updateClients(int,QString,int)),
            this,SLOT(updateClients(int,QString,int)));  //���¿ͻ�����Ϣ
    connect(tcpClientSocket,SIGNAL(disconnected(int)),this,  //�Ͽ�����
            SLOT(slotDisconnected(int)));

    tcpClientSocket->setSocketDescriptor(socketDescriptor);

    tcpClientSocketList.append(tcpClientSocket);   //�������ӵ��б�
    tcpFilenameList.append("");
}

void Server::updateClients(int descriptor,QString msg,int length)  //���¿ͻ�����Ϣ
{
    for(int i=0;i<tcpClientSocketList.count();i++)
    {
        QTcpSocket *item = tcpClientSocketList.at(i);
        if(item->socketDescriptor()==descriptor)
        {
            if(tcpFilenameList[i].isEmpty())
            {
                    if(length > 100)
                    {
                            return;
                    }
                    tcpFilenameList[i] = msg;                          //�����ļ���
            }
            else
            {
                    emit updateServer(tcpFilenameList[i],msg,length);   //���� ���·������� �źţ�
            }
            return;
        }
    }
}

void Server::slotDisconnected(int descriptor)   //�Ͽ�����
{
	
    for(int i=0;i<tcpClientSocketList.count();i++)
    {
        QTcpSocket *item = tcpClientSocketList.at(i);
        if(item->socketDescriptor()==descriptor)
        {
            emit input_end(tcpFilenameList[i]);
            tcpClientSocketList.removeAt(i);  //���б���ɾ��
            tcpFilenameList.removeAt(i);
            return;
        }
    }
    return;
}
