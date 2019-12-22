#ifndef WORKTHREAD2_H
#define WORKTHREAD2_H

#include <QThread>
#include <QStringList>

class WorkThread2 : public QThread
{
    Q_OBJECT

public:
    WorkThread2();
    void stop();

protected:
    void run();

private:
    volatile bool stopped;
    QStringList files;
signals:
    void print_ing(QString);
    void print_start(QString);
    void print_end();
public slots:
    void add_file(QString);
};

#endif 
