#include "tcpclientsocket.h"

TcpClientSocket::TcpClientSocket(QObject *parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));  //��������
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));  //�Ͽ�����
}

void TcpClientSocket::dataReceived()  //��������
{
    while(bytesAvailable()>0)
    {
        int length;
        char buf[1025];    //���뻺����
        length = read(buf,bytesAvailable() > 1024 ? 1024 : bytesAvailable());  //��ȡ����
        buf[length] = '\0';
        QString msg=buf;
        emit updateClients(this->socketDescriptor(),msg,length);  //�����¿ͻ����ź�
    }
}

void TcpClientSocket::slotDisconnected()  //�Ͽ�����
{
    emit disconnected(this->socketDescriptor());  //���Ͽ������ź�
}
