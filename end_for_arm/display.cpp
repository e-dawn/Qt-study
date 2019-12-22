#include "display.h"
#include "ui_display.h"

#include "adc.h"
#include "http.h"
#include "led_ctl.h"
display::display(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::display)
{
    ui->setupUi(this);
    //设置无系统边框
    this -> setWindowFlags(Qt::FramelessWindowHint);
    //this->showFullScreen();                   //设置全屏显示
    closeButton= new QPushButton(this);
    closeButton->setGeometry(5,5,40,40);
    closeButton->setFlat(true);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    led_fd = init_led();
    //设置定时器用于数据采集和更新
    timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(update()));
    timer2->start(600);
    update();
    ff = 0;
}

display::~display()
{
    delete ui;
    delete timer2;
    delete closeButton;
}

void display::changeEvent(QEvent *e)
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

void display::update()
{
    unsigned char ku[10] = {0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    float ad1, ad2, ad3;
    ad1 = get_value(0)*3.3;
    ad2 = get_value(1)*100;
    ad3 = get_value(2)*1024-512;
    char buf[100];

    sprintf(buf, "http://192.168.0.195/add.php?ad1=%d&ad2=%d&ad3=%d", (int)(((float)GetADresult(0)*100)/1024.0)-20, (int)(((float)GetADresult(1)*100)/1024.0)-20, (int)(((float)GetADresult(2)*100)/1024.0)-20);
        //puts(buf);
        http_get(buf);

    ui->lcdNumber_2->display(ad1); //显示实时电压
    ui->lcdNumber_3->display(ad2); //以百分比显示
    ui->lcdNumber_4->display(ad3);

    change_led(ad2, led_fd);
    int d=((float)GetADresult(0)*9)/1024.0;
    cu[7] = ku[d];
    write(led_fd, cu, 8);
    for(int j = 0; j < 7; j++){
    cu[j] = cu[j+1];
    }
}
void display::showe()
{
    this->show();
}

void display::on_pushButton_clicked()
{
    close();
    timer2->stop();
    if(!ff)
    {
        m = new MainDialog;
        QObject::connect(m, SIGNAL(closes()), this, SLOT(showe()));
        m->exec();
    }
    else
    {
        m->show();
    }
}
