#include "tcpclientsocket.h"

TcpClientSocket::TcpClientSocket(QObject *parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));  //接收数据
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));  //断开连接
}

void TcpClientSocket::dataReceived()  //接收数据
{
    while(bytesAvailable()>0)
    {
        int length;
        char buf[1025];    //输入缓冲区
        length = read(buf,bytesAvailable() > 1024 ? 1024 : bytesAvailable());  //读取数据
        buf[length] = '\0';
        QString msg=buf;
        emit updateClients(this->socketDescriptor(),msg,length);  //发更新客户端信号
    }
}

void TcpClientSocket::slotDisconnected()  //断开连接
{
    emit disconnected(this->socketDescriptor());  //发断开连接信号
}
