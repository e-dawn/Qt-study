#include "maindialog.h"
#include "ui_maindialog.h"
#include <stdlib.h>            //产生随机数
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
    //设置无系统边框
    this -> setWindowFlags(Qt::FramelessWindowHint);
    QPushButton *closeButton= new QPushButton(this);
    closeButton->setGeometry(5,5,40,40);
    closeButton->setFlat(true);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    //初始化开关状态
    state1 = 0;
    state2 = 0;
    state3 = 0;
    state4 = 0;
    //设置定时器用于时间更新
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
    showTime();
    //设置定时器用于数据采集和更新
    timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(update()));
    timer2->start(500);
    update();
    //隐藏电机控制区
    ui->widget->hide();
}

//直流电机控制开关
void MainDialog::on_pushButton_clicked()
{
    if(!state1)
    {
        if(1)//打开电机
        {
            QIcon icon;
            icon.addFile(":/images/off.png");
            ui->pushButton->setIcon(icon);

            ui->widget->show(); //显示电机控制区域

            state1 = true;
        }
        else
        {
            qDebug()<< "open error"<< endl;
        }
    }
    else
    {
        //stop_dcmotor();                //关闭电机
        QIcon icon;
        icon.addFile(":/images/on.png");
        ui->pushButton->setIcon(icon);

        ui->widget->hide();             //隐藏电机控制区域
        state1 = false;
    }
}

//LED模拟温度采集
void MainDialog::on_pushButton_2_clicked()
{
    if(!state2)
    {
        if(1)                                //打开LED显示设备
        {
            //change_led(10);                //改变LED显示
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
        //led_close();                      //关闭LED显示设备
        QIcon icon;
        icon.addFile(":/images/on.png");
        ui->pushButton_2->setIcon(icon);
        state2 = false;
    }
}

//广告屏按钮
void MainDialog::on_pushButton_3_clicked()
{
    if(!state3)
    {
        //QString program = "a.out";
        //myProcess.start(program);         //新建进程，打开模拟广告屏
        QIcon icon;
        icon.addFile(":/images/off.png");
        ui->pushButton_3->setIcon(icon);
        state3 = true;
    }
    else
    {
        //QString program = "stop.sh";     //执行关闭脚本
        //myProcess1.start(program);
        QIcon icon;
        icon.addFile(":/images/on.png");
        ui->pushButton_3->setIcon(icon);
        state3 = false;
    }
}

//时间显示槽函数
void MainDialog::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    ui->lcdNumber->display(text);
}

//电机转速更新
void MainDialog::on_horizontalSlider_valueChanged(int value)
{
    //changeV_dcmotor(value);
}

//采集ADC数据并显示
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
    if(state4) //通过ADC POT2控制电机转速
    {
        ui->horizontalSlider->setValue((int)t -512);
    }
}

//ADC控制电机使能开关
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
