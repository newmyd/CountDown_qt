#include "thread.h"

Thread::Thread()
{
    //
}

void Thread::run()
{
    for(flag = true; flag; usleep(100))
        emit showtim(0);
    return ;
}

void Thread::stop()
{
    flag = false;
    quit();
    wait();
}
