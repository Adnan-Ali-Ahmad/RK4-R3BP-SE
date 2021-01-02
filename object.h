#ifndef OBJECT_H
#define OBJECT_H
#include <stdio.h>
#include <fstream>
#include <iostream>

using namespace std;

class object
{
    public:
        double m,R,T;
        double a,e,i,w,Om,M;
        double x,y,z;
        double vx,vy,vz;
        double rho;
        double density;

        object(double m=0.,double R=0.,double T=0.,double density=0.,double a=0.,double e=0.,double i=0.,double w=0.,double Om=0.,double M=0.);
        ~object();

        void write_out(ofstream& file){
            file<<x<<"\t"<<y<<"\t"<<z<<"\t"<<vx<<"\t"<<vy<<"\t"<<vz<<"\t"<<m<<"\t"<<T<<"\t"<<R<<endl;
        }

        void print_out(){
        cout <<"x= "<<x<<"\t"<<"y= "<<y<<"\t"<<"z= "<<z<<"\t"<<"vx= "<<vx<<"\t"<<"vy= "<<vy<<"\t"<<"vz= "<<vz<<endl;
        }

        void write_out_keplerian(ofstream& file){
            file<<a<<"\t"<<e<<"\t"<<i<<"\t"<<w<<"\t"<<Om<<"\t"<<M<<endl;
        }

        void print_out_keplerian(){
            cout<<a<<"\t"<<e<<"\t"<<i<<"\t"<<w<<"\t"<<Om<<"\t"<<M<<endl;
        }

    protected:

    private:
};

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


#endif // OBJECT_H

