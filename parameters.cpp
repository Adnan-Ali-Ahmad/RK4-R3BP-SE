#include "parameters.h"

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
