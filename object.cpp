#include <object.h>


object::object(double m,double R,double T,double density,double a,double e,double i,double w,double Om,double M)
{
    this->m = m;
    this->R = R;
    this->T = T;
    this->x = x;
    this->y = y;
    this->z = z;
    this->vx = vx;
    this->vy = vy;
    this->vz = vz;
    this->a = a;
    this->e = e;
    this->i = i;
    this->w = w;
    this->Om = Om;
    this->M = M;
    this->density = density;
}

object::~object()
{
    //dtor
}
