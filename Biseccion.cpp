#include <iostream>
#include <cmath>
using namespace std;


const double ErrMax=1e-7;

double f(double x){
    return sin(x)/x;
}

double CerosPorBiseccion(double a, double b){
    double x, m,fa,fm;
    
    fa=f(a);
    while (b-a>ErrMax){
        m=(a+b)/2; fm=f(m);
        if (fa*fm>0)    
            {a=m; fa=fm;}
        else
            b=m;
    }
    return (a+b)/2;

}


int main(){
    double a=2, b=4;
    
   cout<<"El cero es " <<CerosPorBiseccion(a,b) <<endl;

   return 0;

    //for (double x =0.1; x<=10; x+=0.1)
    
    //cout<<x<<" "<<f(x) << endl;
    
    //return 0;
}