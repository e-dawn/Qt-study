#include "login.h"
#include "ui_logindialog.h"


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
    QPushButton *closeButton= new QPushButton(this);
    closeButton->setGeometry(5,5,40,40);
    closeButton->setFlat(true);
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
    cnt = cnt+1%100;
        ui->progressBar->setValue(cnt);
        ui->progressBar_2->setValue(cnt);
        ui->progressBar_3->setValue(cnt);
        if(ui->progressBar->value() == 13 && ui->progressBar_2->value() == 13 && ui->progressBar_3->value() == 13)
        {
            accept();
        }
}
