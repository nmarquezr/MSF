#include <iostream>
#include <cmath>
#include <math.h>
using namespace std;

// Constantes globales
const double GM=1.0;


//Declaracion clases
class Cuerpo;
//_________________Clase Cuerpo_____________________
class Cuerpo{   
    private:
        double x,y,Vx,Vy,Fx,Fy,m,R;
    public:
        void Start(double x0, double y0, double Vx0, double Vy0, double m0, double R0);
        void CalculeForce(void);
        void Move(double dt);
        double Getx(void){return x;};
        double Gety(void){return y;};
};

void Cuerpo::Start(double x0, double y0, double Vx0, double Vy0, double m0, double R0 ){
    x=x0; y=y0; Vx=Vx0; Vy=Vy0; m=m0; R=R0;
}
void Cuerpo::CalculeForce(void){
    double aux =GM*m*pow(x*x+y*y,-1.5); 
    Fy=-aux*y; Fx=-aux*x; 

}
void Cuerpo::Move(double dt){
    CalculeForce();
    x+=Vx*dt; y+=Vy*dt;
    Vx+=Fx/m*dt; Vy+=Fy/m*dt;
}
//_____Funciones Globales_______

int main(){
Cuerpo Planet;
double r=10, m=1;
double w,V0, T;
double t, dt=0.1;

w = sqrt(GM/(r*r*r));
V0 = w*r;
T = 2*M_PI/w;


//  _______(x0,y0,Vx0,Vy0,m0,R0)
Planet.Start(r,0,0,V0,m,0.5);
for(t=0;t<1.01*T; t+=dt){
    cout<<Planet.Getx()<<" "<<Planet.Gety()<<endl;
    Planet.CalculeForce();
    Planet.Move(dt);   
}
return 0;
    
}