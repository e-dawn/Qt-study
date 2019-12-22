#include "tcpserver.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include "ui_dialog.h"
#include "workthread.h"
#include "workthread2.h"

#define SHURUJING "./shurujing/"
#define SHUCHUJING "./shuchujing/"
QQueue<work_ctl> work_list;

WorkThread *workThread;
WorkThread2 *workThread2;

TcpServer::TcpServer(QWidget *parent) :QDialog(parent),ui(new Ui::TcpServer)
{
    ui->setupUi(this);

    port=8010;

    workThread=new WorkThread();
    workThread2=new WorkThread2();
    connect(workThread2, SIGNAL(print_ing(QString)), this, SLOT(add_print(QString)));
    connect(workThread2, SIGNAL(print_start(QString)), this, SLOT(start_print(QString)));
    connect(workThread2, SIGNAL(print_end()), this, SLOT(clear_print()));
    connect(this, SIGNAL(shuchulist(QString)), workThread2, SLOT(add_file(QString)));
    connect(workThread, SIGNAL(shuchu_ing(QString)), this, SLOT(add_shuchu(QString)));
    slotCreateServer();
}


void slotStart()
{

    if (!workThread->isRunning()){
        workThread->start();
    }
}

void slotStop()
{

    if (workThread->isRunning()){
        workThread->stop();
    }
}

void slotStart2()
{

    if (!workThread2->isRunning()){
        workThread2->start();
    }
}

void slotStop2()
{
    if (workThread2->isRunning()){
        workThread2->stop();
    }
}


TcpServer::~TcpServer()
{
    slotStop();
    slotStop2();
}



void TcpServer::slotCreateServer()  //创建服务器
{
    server = new Server(this,port);
    connect(server,SIGNAL(updateServer(QString,QString,int)),this,
            SLOT(updateServer(QString,QString,int)));  //更新服务器端显示
	connect(server,SIGNAL(input_end(QString)), this, SLOT(creat_work_ctl(QString)));
}


void TcpServer::creat_work_ctl(QString file_name)
{
        work_ctl t;
        t.filename = file_name;
        t.start_time = QTime::currentTime();
        ui->listWidget->addItem(file_name);
        work_list.append(t);
        slotStart();
}




void TcpServer::updateServer(QString name,QString msg,int length)  //输入井
{
    QDir dir;
    if (!dir.exists(SHURUJING))
    {
            dir.mkpath(SHURUJING);
    }
    QFile data(SHURUJING+name);
    if(data.open(QFile::WriteOnly|QFile::Append))
    {
        QTextStream out(&data);
        out<<msg;
    }
    data.close();
}

void TcpServer::add_shuchu(QString name)
{
    QListWidgetItem *item1 = ui->listWidget->takeItem(0);
    ui->listWidget->removeItemWidget(item1);
    delete item1;
    ui->listWidget_2->addItem(name);
    emit shuchulist(name);
    slotStart2();

}

void TcpServer::del_shuchu()
{
    QListWidgetItem *item1 = ui->listWidget_2->takeItem(0);
    ui->listWidget->removeItemWidget(item1);
    delete item1;
}

void TcpServer::clear_print()
{
    ui->textEdit->clear();
    del_shuchu();
    ui->label_5->setText(tr("未进行打印"));
}

void TcpServer::start_print(QString name)
{
    ui->label_5->setText(name);
}

void TcpServer::add_print(QString msg)
{
    QString text = ui->textEdit->toPlainText();
    text += msg;
    ui->textEdit->setPlainText(text);
    ui->textEdit->moveCursor(QTextCursor::End);
}


