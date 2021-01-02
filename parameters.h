#ifndef PARAMETERS_H
#define PARAMETERS_H
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

class parameters
{
    public:

		double mls,vwind,C;
        
        parameters(double mls =0.,double vwind=0.,double C=0.); 
        ~parameters();

    protected:

    private:
};

parameters::parameters(double mls,double vwind,double C)
{
    this->mls = mls;
    this->vwind = vwind;
    this->C = C;
}

parameters::~parameters()
{
    //dtor
}

#endif // PARAMETERS_H
