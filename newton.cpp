#include "iostream"
#include "math.h"
using namespace std;

	double posicion(double v, double h,double t){
		return h + v*t - (9.81 / 2)*t*t;
	}

	double derivada(double v, double t){
		return v - 9.81*t;
	}

int main(){

  	double v, h, der, pos, x0, x1, t;

	cout << "Ingrese una altura\n";
	cin >> h;
	cout << "Ingrse la velocidad inical\n";
	cin >> v;
	cout << endl;
	cout << "Ingrese un tiempo inicial\n";
	cin >> t;
	
	int iter = 0;
	x0 = t - posicion(v, h, t) / derivada(v, t);
	while(iter < 1000){
		x1 = x0 - posicion(v, h, x0) / derivada(v, x0);
		if( fabs(x0 - x1) < 0.00001 ) break;
		else x0 = x1;
		iter++;
	}

	cout << "Se tarda " << x1 << " segundos\n" << "Se realizo en " << iter << " iteraciones\n";
	
}
