#include <iostream>
#include <cmath>
using namespace std;

const double w =3.0;

// Dos ecuaciones diferenciales acopladas f1 y f2  

double f1(double t,double x1,double x2){
    return x1*(1-x1-x2); //Funcion a integrar
}

double f2(double t,double x1,double x2){
    return x2*(1+x1-x2); //Funcion a integrar
}



void UnPasoDeRK4(double & t0,double & x10,double & x20, double dt){
double dx11, dx21, dx31, dx41;              double dx12, dx22, dx32, dx42;
dx11=dt*f1(t0,x10,x20);                     dx12=dt*f2(t0,x10,x20);
dx21=dt*f1(t0+dt/2,x10+dx11/2,x20+dx12/2);   dx22=dt*f2(t0+dt/2,x10+dx11/2,x20+dx12/2);
dx31=dt*f1(t0+dt/2,x10+dx21/2,x20+dx22/2);  dx32=dt*f2(t0+dt/2,x10+dx21/2,x20+dx22/2);
dx41=dt*f1(t0+dt,x10+dx31,x20+dx32);             dx42=dt*f2(t0+dt,x10+dx31,x20+dx32);
x10+=(dx11+2*(dx21+dx31)+dx41)/6; t0+=dt;       x20+=(dx12+2*(dx22+dx32)+dx42)/6; 
}

int main(){
    double t, x1,x2; double dt = 0.01;
    for (t=0, x1=0.25, x2=0.25; t<1000;){
        cout<<t<<" "<<x2<< endl;
        UnPasoDeRK4(t,x1,x2,dt);
    }
    return 0;
    
}


