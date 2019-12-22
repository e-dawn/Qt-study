#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QHostAddress>
#include <QTcpSocket>
#include <QFileInfo>


namespace Ui {
    class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT
public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Dialog *ui;
    QHostAddress *serverIP;
    QTcpSocket *tcpSocket;

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // DIALOG_H
