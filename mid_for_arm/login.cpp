#include "login.h"
#include "ui_logindialog.h"
#include "adc.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    init();
}

void LoginDialog::init()
{
    //������ϵͳ�߿�
    this -> setWindowFlags(Qt::FramelessWindowHint);
    //�رհ�ť
    closeButton= new QPushButton(this);
    closeButton->setGeometry(5,5,40,40);
    closeButton->setFlat(true);

    init_ADdevice();     //��ʼ��ADC�豸

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    //���ö�ʱ����ˢ������
    timer = new QTimer(this);
    cnt = 0;
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(800);
    update();
}


LoginDialog::~LoginDialog()
{
    delete ui;
    delete timer;
    delete closeButton;
    close_adc();
}

void LoginDialog::changeEvent(QEvent *e)
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

void LoginDialog::update()
{
    ui->progressBar->setValue(get_value(0)*100);
    ui->progressBar_2->setValue(get_value(1)*100);
    ui->progressBar_3->setValue(get_value(2)*100);
    if(ui->progressBar->value() == 13 && ui->progressBar_2->value() == 13 && ui->progressBar_3->value() == 13)
    {
        accept();
    }
}
