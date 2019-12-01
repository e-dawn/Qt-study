#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QTime>
#include <QTimer>
#include <QPushButton>

namespace Ui {
    class LoginDialog;
}

class LoginDialog : public QDialog {
    Q_OBJECT
public:
    LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::LoginDialog *ui;
    QTimer *timer;
    int cnt;
    void init();

private slots:
    void update();
};

#endif // LOGIN_H
