#ifndef SLAVE_H
#define SLAVE_H

#include <mpi.h>
#include <iostream>
#include <windows.h>

using namespace std;

class Slave
{
public:
    Slave();
    ~Slave();

    void run(); 

};

#endif