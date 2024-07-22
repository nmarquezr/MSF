#include <iostream>
#include <cmath>
#include "vector.h"


using namespace std;

int main(void){
    vector3D v(1, 2, 3);
    v.load(1, 2, 3);
    cout << "v = " << v << endl;

    return 0;
}
