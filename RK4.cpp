#include <iostream>
#include <cmath>
using namespace std;


double f(double t,double x){
    return exp(-t*t); //Funcion a integrar
}
    

void UnPasoDeRK4(double & t0,double & x0, double dt){
double dx1, dx2,dx3,dx4;
dx1=dt*f(t0,x0);
dx2=dt*f(t0+dt/2,x0+dx1/2);
dx3=dt*f(t0+dt/2,x0+dx2/2);
dx4=dt*f(t0+dt,x0+dx3);
x0+=(dx1+2*dx2+2*dx3+dx4)/6; t0+=dt;
}

int main(){
    double t, x; double dt=0.1;
    for (t=0,x=0; t< 2+dt/2;){
        cout<<t<<" "<<x<<" " <<exp(t)<< endl;
        UnPasoDeRK4(t,x,dt);
    }
    return 0;
    
}


