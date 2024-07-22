#include <iostream>
#include <cmath>
#include "Random64.h"
using namespace std;

const double w = 3.0;

// Tres ecuaciones diferenciales acopladas f1, f2 y f3

double f1(double t, double x1, double x2, double x3) {
    return x1 * (1 - x1 - x2 - x3); // Función a integrar
}

double f2(double t, double x1, double x2, double x3) {
    return x2 * (1 + x1 - x2 - x3); // Función a integrar
}

double f3(double t, double x1, double x2, double x3) {
    return x3 * (1 + x2 + x1 - x3); // Función a integrar
}

void UnPasoDeRK4(double &t0, double &x10, double &x20, double &x30, double dt) {
    double dx11, dx21, dx31, dx41;
    double dx12, dx22, dx32, dx42;
    double dx13, dx23, dx33, dx43;

    dx11 = dt * f1(t0, x10, x20, x30);                     dx12 = dt * f2(t0, x10, x20, x30);                     dx13 = dt * f3(t0, x10, x20, x30);
    dx21 = dt * f1(t0 + dt / 2, x10 + dx11 / 2, x20 + dx12 / 2, x30 + dx13 / 2);   dx22 = dt * f2(t0 + dt / 2, x10 + dx11 / 2, x20 + dx12 / 2, x30 + dx13 / 2);   dx23 = dt * f3(t0 + dt / 2, x10 + dx11 / 2, x20 + dx12 / 2, x30 + dx13 / 2);
    dx31 = dt * f1(t0 + dt / 2, x10 + dx21 / 2, x20 + dx22 / 2, x30 + dx23 / 2);   dx32 = dt * f2(t0 + dt / 2, x10 + dx21 / 2, x20 + dx22 / 2, x30 + dx23 / 2);   dx33 = dt * f3(t0 + dt / 2, x10 + dx21 / 2, x20 + dx22 / 2, x30 + dx23 / 2);
    dx41 = dt * f1(t0 + dt, x10 + dx31, x20 + dx32, x30 + dx33);                 dx42 = dt * f2(t0 + dt, x10 + dx31, x20 + dx32, x30 + dx33);                 dx43 = dt * f3(t0 + dt, x10 + dx31, x20 + dx32, x30 + dx33);

    x10 += (dx11 + 2 * (dx21 + dx31) + dx41) / 6; t0 += dt;
    x20 += (dx12 + 2 * (dx22 + dx32) + dx42) / 6;
    x30 += (dx13 + 2 * (dx23 + dx33) + dx43) / 6;
}

int main() {
    
    double t, x1, x2, x3; double dt = 0.01;
    Crandom ran64(0); // Semilla
    double mu = 0.5, sigma = 0.1; // Parámetros de la distribución normal
    
    x1=sigma*sqrt(-2*log(ran64.r()))*cos(2*M_PI*ran64.r())+mu; x2=sigma*sqrt(-2*log(ran64.r()))*cos(2*M_PI*ran64.r())+mu; x3=sigma*sqrt(-2*log(ran64.r()))*cos(2*M_PI*ran64.r())+mu;

        for (t = 0, x1 = x1, x2 = x2, x3 = x3; t < 100;) {
        cout << x1<< " " << x2 <<" "<<x3<< endl; // Modificar según lo que se quiera observar
        UnPasoDeRK4(t, x1, x2, x3, dt);
    }    

    return 0;
}