#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>

class WorkThread : public QThread
{
    Q_OBJECT

public:
    WorkThread();
    void stop();

protected:
    void run();

private:
    volatile bool stopped;
signals:
    void shuchu_ing(QString);
};

#endif 
