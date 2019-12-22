#ifndef DISPLAY_H
#define DISPLAY_H

#include <QDialog>
#include "maindialog.h"
namespace Ui {
    class display;
}

class display : public QDialog {
    Q_OBJECT
public:
    display(QWidget *parent = 0);
    ~display();
    QTimer *timer2;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::display *ui;

    QPushButton *closeButton;
    void init();
    char cu[10];
    int led_fd;
    bool ff;
    MainDialog *m;
signals:
    void closes();

private slots:
    void on_pushButton_clicked();
    void update();
    void showe();
};

#endif // DISPLAY_H
