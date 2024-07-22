#include <iostream>
#include <cmath>
using namespace std;

double f(double x){
    return sin(x)/x;
}


const double ErrMax=1e-7;

int main(){
    double x;
    double a=2, b=4, m,fa,fm;
    fa=f(a); 
    while (b-a>ErrMax){
        m=(a+b)/2; fm=f(m);
        if (fa*fm >0)
            {a=m; fa=fm;}
        else 
            b=m;

        
    }
   cout<<"El cero es " <<(a+b)/2<<endl;

   return 0;

    //for (double x =0.1; x<=10; x+=0.1)
    
    //cout<<x<<" "<<f(x) << endl;
    
    //return 0;
}