#include <QApplication>
#include "login.h"
#include "maindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog login;
    if(login.exec() == QDialog::Accepted)
    {
        MainDialog m;
        m.show();
        return a.exec();
    }
    return 0;
}
