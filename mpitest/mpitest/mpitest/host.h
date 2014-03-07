#ifndef HOST_H
#define HOST_H

#include <mpi.h>
#include <boost/thread.hpp>
#include <windows.h>
#include <iostream>

using namespace std;

enum WorkStatus{NOWORK, WORK, COMPLETE};

class Host
{
public:
    Host();
    ~Host();

    void run();

private:
    void hostwork();

private:
    WorkStatus mWorkStatus;
};

#endif