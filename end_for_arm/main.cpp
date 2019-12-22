#include <QApplication>
#include "login.h"
#include "maindialog.h"
#include "display.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog login;
    if(login.exec() == QDialog::Accepted)
    {
        display m;
        m.show();
        return a.exec();
    }
    return 0;
}
