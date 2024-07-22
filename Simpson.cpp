#include <iostream>
#include <cmath>
using namespace std;


const double ErrMax=1e-7;

double f(double x){
    return cos(x) ;
}

double IntegralSimpson(double a, double b, int n){
    double x, h,suma; int i;
    n*=2; h=(b-a)/n;
    
    for (suma=0, i=0; i<=n;i++){
        x=a+i*h;
        if (i==0 || i==n) //Primero y ultimo
        suma+=f(x);
        else if(i%2==0) //Pares
        suma+=f(x)*2;
        else            //Impares
        suma+=f(x)*4; 
    }
    return suma*h/3;

}


int main(){
    double a=0, b=M_PI/2, n=50;

    
   cout<<"La integral es " <<IntegralSimpson(a,b,n) <<endl;

   return 0;

    //for (double x =0.1; x<=10; x+=0.1)
    
    //cout<<x<<" "<<f(x) << endl;
    
    //return 0;
}