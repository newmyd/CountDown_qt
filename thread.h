#ifndef THREAD_H
#define THREAD_H

#include <QThread>

class Thread : public QThread{
    Q_OBJECT

public:
    Thread();  //构造函数
    void stop();

signals:
    void showtim(int);

protected:
    void run();

private:
    bool flag;
};

#endif // THREAD_H
