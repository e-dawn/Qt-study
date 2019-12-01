#include "maindialog.h"
#include "ui_maindialog.h"
#include <stdlib.h>            //���������
#include <QDebug>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    init();
}

MainDialog::~MainDialog()
{
    delete ui;
    delete timer;
    delete timer2;
}

void MainDialog::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainDialog::init()
{
    //������ϵͳ�߿�
    this -> setWindowFlags(Qt::FramelessWindowHint);
    QPushButton *closeButton= new QPushButton(this);
    closeButton->setGeometry(5,5,40,40);
    closeButton->setFlat(true);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    //��ʼ������״̬
    state1 = 0;
    state2 = 0;
    state3 = 0;
    state4 = 0;
    //���ö�ʱ������ʱ�����
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
    showTime();
    //���ö�ʱ���������ݲɼ��͸���
    timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(update()));
    timer2->start(500);
    update();
    //���ص��������
    ui->widget->hide();
}

//ֱ��������ƿ���
void MainDialog::on_pushButton_clicked()
{
    if(!state1)
    {
        if(1)//�򿪵��
        {
            QIcon icon;
            icon.addFile(":/images/off.png");
            ui->pushButton->setIcon(icon);

            ui->widget->show(); //��ʾ�����������

            state1 = true;
        }
        else
        {
            qDebug()<< "open error"<< endl;
        }
    }
    else
    {
        //stop_dcmotor();                //�رյ��
        QIcon icon;
        icon.addFile(":/images/on.png");
        ui->pushButton->setIcon(icon);

        ui->widget->hide();             //���ص����������
        state1 = false;
    }
}

//LEDģ���¶Ȳɼ�
void MainDialog::on_pushButton_2_clicked()
{
    if(!state2)
    {
        if(1)                                //��LED��ʾ�豸
        {
            //change_led(10);                //�ı�LED��ʾ
            QIcon icon;
            icon.addFile(":/images/off.png");
            ui->pushButton_2->setIcon(icon);
            state2 = true;
        }
        else
        {
            qDebug("open error");
        }
    }
    else
    {
        //led_close();                      //�ر�LED��ʾ�豸
        QIcon icon;
        icon.addFile(":/images/on.png");
        ui->pushButton_2->setIcon(icon);
        state2 = false;
    }
}

//�������ť
void MainDialog::on_pushButton_3_clicked()
{
    if(!state3)
    {
        //QString program = "a.out";
        //myProcess.start(program);         //�½����̣���ģ������
        QIcon icon;
        icon.addFile(":/images/off.png");
        ui->pushButton_3->setIcon(icon);
        state3 = true;
    }
    else
    {
        //QString program = "stop.sh";     //ִ�йرսű�
        //myProcess1.start(program);
        QIcon icon;
        icon.addFile(":/images/on.png");
        ui->pushButton_3->setIcon(icon);
        state3 = false;
    }
}

//ʱ����ʾ�ۺ���
void MainDialog::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    ui->lcdNumber->display(text);
}

//���ת�ٸ���
void MainDialog::on_horizontalSlider_valueChanged(int value)
{
    //changeV_dcmotor(value);
}

//�ɼ�ADC���ݲ���ʾ
void MainDialog::update()
{
    float t;
    int b;
    if(state2)
    {
        b = rand()%20;
        //change_led(b);
        ui->lcdNumber_5->display(b);
        ui->lcdNumber_2->display(rand()%4);
        ui->lcdNumber_3->display(rand()%100);
        t = rand()%1024;
        ui->lcdNumber_4->display(t);
    }
    else
    {
        ui->lcdNumber_2->display(rand()%4);
        ui->lcdNumber_3->display(rand()%100);
        t = rand()%1024;
        ui->lcdNumber_4->display(t);
    }
    if(state4) //ͨ��ADC POT2���Ƶ��ת��
    {
        ui->horizontalSlider->setValue((int)t -512);
    }
}

//ADC���Ƶ��ʹ�ܿ���
void MainDialog::on_pushButton_4_clicked()
{
    if(!state4)
    {
        QIcon icon;
        icon.addFile(":/images/zoomnormal.png");
        ui->pushButton_4->setIcon(icon);
        state4 = true;
    }
    else
    {
        QIcon icon;
        icon.addFile(":/images/apply.png");
        ui->pushButton_4->setIcon(icon);
        state4 = false;
    }
}
