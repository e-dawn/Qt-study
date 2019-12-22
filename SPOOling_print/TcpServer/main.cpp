#include <QtGui/QApplication>
#include "tcpserver.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    TcpServer w;
    w.show();
    return a.exec();
}
