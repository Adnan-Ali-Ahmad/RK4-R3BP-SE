#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cmath>
#include "object.h"
#include <ctime>
#include "distances.h"
#include "parameters.h"
#include "my_functions.hpp"
//#include <mpi.h>

using namespace std;

double pi = acos(-1.);
double G = 6.67408e-11;
double k = 1.38064852e-23;
double mh = 1.67e-27;
double nh = 1e16;
double sigma = 5.67e-8;
double Tmed = 2500.;

int main(int argc, char* argv[]){

    srand(time(NULL)); //for random generation purposes

  	//initialize MPI
	// MPI_Init(NULL, NULL);
 //  	int world_rank;
	// MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	// int world_size;
	// MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int N_ast;
	double Stime;
	try{
		N_ast = std::stoi(argv[1]); //number of asteroids
		Stime = std::stod(argv[2]); //simulation time in number of orbital periods of closest ast to sun
	}
		catch (const std::exception &exc){
		std::cerr<<"ERROR: Please provide number of asteroids and simulation time"<<std::endl;
		exit(1);
	}

	// N_ast = round(N_ast/world_size);
	std::cout<<Stime<<std::endl;

    object sun(1.989e30,195.*695510e3,5000.);
    object jup(1.89813e27,69911e3,0.,1330.,5.20336301,0.04839266,0.,14.75385,100.55615,34.40438); //Jupiter
    object COM(0.); //center of mass
    parameters P(sun.m*1e-8,5e3,0.9);

    object M1 = sun; //copies
    object M2 = jup;

    double GM = G*(sun.m);
    double T = Stime*orbital_period(GM,1.);//0.5*1e6*orbital_period(GM,1.); //simulation time
    int it = 0;
    double dt; //time step
    int snapshot = 9000;
    double t = 0.; //secs
    double t0 = 0.; //J2000 epoch

    get_cartesian(GM,t,t0,sun);
    get_cartesian(GM,t,t0,jup);
    update_COM(COM,jup,sun);
    
    object ast[N_ast];
    object M3[N_ast]; //asteroid copies
    distances SIM[N_ast];

    // ofstream file1("Outputs/process"+to_string(world_rank)+"_a0.txt");
    // ofstream file2("Outputs/process"+to_string(world_rank)+"_a.txt");
    // ofstream file3("Outputs/process"+to_string(world_rank)+"_initial_distribution.txt");
    // ofstream file4("Outputs/process"+to_string(world_rank)+"_final_distribution.txt");
    // ofstream file5("Outputs/process"+to_string(world_rank)+"_jup.txt");
    // ofstream file6("Outputs/process"+to_string(world_rank)+"_ast_kep.txt");
    // ofstream file7("Outputs/process"+to_string(world_rank)+"_t.txt");
    // ofstream file8("Outputs/process"+to_string(world_rank)+"_jup_kep.txt");

    ofstream file1("Outputs/a0.txt");
    ofstream file2("Outputs/a.txt");
    ofstream file3("Outputs/initial_distribution.txt");
    ofstream file4("Outputs/final_distribution.txt");
    ofstream file5("Outputs/jup.txt");
    ofstream file6("Outputs/ast_kep.txt");
    ofstream file7("Outputs/t.txt");
    ofstream file8("Outputs/jup_kep.txt");


    // for(int i=0;i<N_ast;i++){
    //     ofstream file;
    //     file.open("../Outputs_KWINDS/traj/ast"+to_string(i)+".txt");
    // }


    for(int i=0;i<N_ast;i++){
        ast[i].a = 2.9;//fRand(2.,3.5);
        ast[i].M = fRand(0.,360.);
        ast[i].i = fRand(0.,5.);
        ast[i].e = 0.01;//fRand(0.,0.02);
        ast[i].density = 2000.;
        ast[i].R = 4300.;//fRand(1000.,10e3);
        std::cout<<"Asteroid size: "<<ast[i].R<<" m"<<std::endl;
        std::cout<<"Asteroid semimajor axis: "<<ast[i].a<<" AU"<<std::endl;
        ast[i].m = 1.33*pi*ast[i].R*ast[i].R*ast[i].R*ast[i].density;
        get_cartesian(GM,t,t0,ast[i]);
        ast[i].write_out_keplerian(file1);
        write_in_COM(ast[i],COM,file3);
    }
    dt = adapt_dt(GM,ast,N_ast,5000.);

    //write_in_COM(jup,COM,file5);
    cout<<"Timestep = "<<dt<<" seconds."<<endl;

    while(t < T){

        if((it%snapshot) == 0){
            // cout<<"Process "<<world_rank<<" Simulation Progress: "<<floor(100.*t/T)+1<<"%\r";
            cout<<" Simulation Progress: "<<floor(100.*t/T)+1<<"%\r";
            
            //update_COM(COM,sun,jup);
            write_in_COM(jup,sun,file5);
            GM = G*(sun.m);
            get_keplerian(GM,jup,sun);
            jup.write_out_keplerian(file8);
            for(int i=0;i<N_ast;i++){
                ofstream file;
                //file.open("../Outputs/traj/ast"+to_string(i)+".txt",fstream::app);
                //write_in_COM(ast[i],sun,file);
                get_keplerian(GM,ast[i],sun); ast[i].write_out_keplerian(file6);
                file7 << t << endl;
            }
        }
        RK4(sun,jup,M1,M2,M3,ast,SIM,P,N_ast,dt);
        t+=dt;
        it+=1;
    }
    update_COM(COM,jup,sun);
    write_in_COM(jup,COM,file5);
    for(int i =0;i<N_ast;i++){
        get_keplerian(GM,ast[i],COM);
        ast[i].write_out_keplerian(file2);
        write_in_COM(ast[i],COM,file4);
    }

	// MPI_Finalize();
    return 0;
}
