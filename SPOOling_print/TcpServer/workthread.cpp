#include "workthread.h"
#include <QtDebug>
#include <QDir>
#include <QStringList>


#define SHURUJING "./shurujing/"
#define SHUCHUJING "./shuchujing/"

WorkThread::WorkThread()
{
    stopped = false;
}

QString buffer;
void shuchujing(QString name)
{
    QDir dir;
    if (!dir.exists(SHUCHUJING))
    {
            dir.mkpath(SHUCHUJING);
    }
    QFile data(SHUCHUJING+name);
    if(data.open(QFile::WriteOnly|QFile::Append))
    {
        QTextStream out(&data);
        out<<buffer<<endl;
    }
    data.close();
}

void WorkThread::run()
{
    QDir dir(SHURUJING);
    QStringList files;
    files = dir.entryList();
    while(files.count() > 2 && !stopped)
    {
        for(int i = 2; i < files.count(); i++)
        {
            QFile file(SHURUJING+files[i]);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
            QTextStream in(&file);

            while (!in.atEnd())
            {
                buffer = in.readLine();
                shuchujing(files[i]);
            }
            file.close();
            emit shuchu_ing(files[i]);
            QFile::remove(SHURUJING+files[i]);

        }
        files = dir.entryList();
    }
    stopped = false;
}

void WorkThread::stop()
{
    stopped = true;
}
