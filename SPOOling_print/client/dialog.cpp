#include "dialog.h"
#include "ui_dialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <windows.h>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Dialog::on_pushButton_clicked()
{
    QFileDialog a(this);
    a.setWindowTitle(tr("ѡ��Ҫ��ӡ���ĵ�"));
    a.setDirectory(".");
    a.exec();
    QString file = a.selectedFiles()[0];
    ui->label->setText(file);
    QString buffer;
    QFileInfo fileInfo(file);
    QString ip = "127.0.0.1";
    tcpSocket = new QTcpSocket(this);  //���� �ͻ���socket
    tcpSocket->connectToHost(ip,8010);  //�����������
    buffer = fileInfo.fileName();
    tcpSocket->write(buffer.toLatin1(),buffer.length());  //�����ļ���
}

void Dialog::on_pushButton_2_clicked()
{
    QString file = ui->label->text();

    QFile f(file);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&f);
    QString buffer;
    int count = 0, now = 0;
    while (!in.atEnd())
    {
        in.readLine();
        count++;
    }
    in.seek(0);

    while (!in.atEnd())
    {
        now++;
        buffer = in.readLine();
        buffer+="\n";
        tcpSocket->write(buffer.toLatin1(),buffer.length());  //�����ļ�����
        ui->progressBar->setValue( (int)(now*1.0/count*100) );
        qDebug() << buffer << buffer.length() << endl;
    }
    f.close();
    tcpSocket->disconnectFromHost();
    QMessageBox::information(this,tr("���"),tr("�ļ�������ɣ���ȴ���ӡ"));
}
