#include "server.h"

Server::Server(QObject *parent,int port)
    :QTcpServer(parent)
{
    listen(QHostAddress::Any,port);  //在port端口对任意地址监听 P344
}

void Server::incomingConnection(int socketDescriptor)  //建立新连接
{
    TcpClientSocket *tcpClientSocket=new TcpClientSocket(this);
    connect(tcpClientSocket,SIGNAL(updateClients(int,QString,int)),
            this,SLOT(updateClients(int,QString,int)));  //更新客户端信息
    connect(tcpClientSocket,SIGNAL(disconnected(int)),this,  //断开连接
            SLOT(slotDisconnected(int)));

    tcpClientSocket->setSocketDescriptor(socketDescriptor);

    tcpClientSocketList.append(tcpClientSocket);   //保存连接到列表
    tcpFilenameList.append("");
}

void Server::updateClients(int descriptor,QString msg,int length)  //更新客户端信息
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
                    tcpFilenameList[i] = msg;                          //保存文件名
            }
            else
            {
                    emit updateServer(tcpFilenameList[i],msg,length);   //发送 更新服务器端 信号，
            }
            return;
        }
    }
}

void Server::slotDisconnected(int descriptor)   //断开连接
{
	
    for(int i=0;i<tcpClientSocketList.count();i++)
    {
        QTcpSocket *item = tcpClientSocketList.at(i);
        if(item->socketDescriptor()==descriptor)
        {
            emit input_end(tcpFilenameList[i]);
            tcpClientSocketList.removeAt(i);  //从列表中删除
            tcpFilenameList.removeAt(i);
            return;
        }
    }
    return;
}
