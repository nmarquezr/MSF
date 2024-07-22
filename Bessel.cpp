#include <iostream>
#include <cmath>
using namespace std;


const double ErrMax=1e-7;   
    
double f(double alpha, double x, double t){
    return cos(alpha*t-x*sin(t));
}

double IntegralSimpson(double alpha, double x,double a, double b, int n){
    double t, h, suma; int i;
    n*=2; h=(b-a)/n;
    for (suma=0, i=0; i<=n;i++){
        t=a+i*h;
        if (i==0 || i==n) //Primero y ultimo
        suma+=f(alpha,x,t);
        else if(i%2==0) //Pares
        suma+=f(alpha,x,t)*2;
        else            //Impares
        suma+=f(alpha,x,t)*4; 
    }
    return suma*h/3;

}

double Bessel(double alpha, double x){
    double a=0, b=M_PI, n=50;
    return 1/M_PI*IntegralSimpson(alpha,x,a,b,n);
}   

int main(){
    double alpha=0, x;
    for (x=0.1; x<=10; x+=0.1){
        cout<<x<<" "<<Bessel(alpha,x) <<endl;
    }
   return 0;
}