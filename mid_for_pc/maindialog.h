#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QTime>
#include <QTimer>
#include <QProcess>
#include <QPushButton>

namespace Ui {
    class MainDialog;
}

class MainDialog : public QDialog {
    Q_OBJECT
public:
    MainDialog(QWidget *parent = 0);
    ~MainDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainDialog *ui;
    bool state1;
    bool state2;
    bool state3;
    bool state4;
    QProcess myProcess;
    QProcess myProcess1;
    QProcess myProcess0;
    QTimer *timer;
    QTimer *timer2;
    void init();

private slots:
    void on_pushButton_4_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void showTime();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void update();
};




#endif // MAINDIALOG_H
