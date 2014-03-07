#ifndef HOST_H
#define HOST_H

#include <mpi.h>
#include <boost/thread.hpp>

#include <iostream>

using namespace std;

class Host
{
public:
    Host();
    ~Host();

    void run();

private:
    void hostwork();
};

#endif