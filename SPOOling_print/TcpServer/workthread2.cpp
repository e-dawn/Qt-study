#include "workthread2.h"
#include <QtDebug>
#include <QDir>
#include <windows.h>

#define SHURUJING "./shurujing/"
#define SHUCHUJING "./shuchujing/"

WorkThread2::WorkThread2()
{
    stopped = false;
}

void WorkThread2::add_file(QString name)
{
    files << name;
}

void WorkThread2::run()
{
    while(!files.isEmpty() && !stopped)
    {

            QString buffer;
            QFile file(SHUCHUJING+files[0]);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
            QTextStream in(&file);
            emit print_start(files[0]);
            while (!in.atEnd())
            {
                buffer = in.readLine();
                buffer+="\n";
                emit print_ing(buffer);
                Sleep(500);
            }
            file.close();
            emit print_end();
            QFile::remove(SHUCHUJING+files[0]);

        files.removeFirst();
    }
    stopped = false;
}

void WorkThread2::stop()
{
    stopped = true;
}
