#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QtGui/QDialog>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include "server.h"
#include <QTime>
#include <QQueue>
#include <QStringList>

namespace Ui {
    class TcpServer;
}


class TcpServer : public QDialog
{
    Q_OBJECT

public:
    TcpServer(QWidget *parent = 0);
    ~TcpServer();

private:
    int port;
    Server *server;
    Ui::TcpServer *ui;

signals:
    void shuchulist(QString);
public slots:
    void slotCreateServer();
    void updateServer(QString,QString,int);
    void creat_work_ctl(QString);
    void add_shuchu(QString);
    void del_shuchu();
    void clear_print();
    void start_print(QString);
    void add_print(QString);

};


struct work_ctl
{
	QString filename;
	QTime start_time;
        QTime end_time;
};

#endif // TCPSERVER_H
