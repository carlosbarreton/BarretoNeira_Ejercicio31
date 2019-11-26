#include <iostream>
#include <fstream>

using namespace std;

void resolver(int Nxx, string archivo);

int main() {
	
	resolver(10, "evolve_A.dat");
	resolver(31, "evolve_B.dat");
	resolver(29, "evolve_C.dat");

	return 0;
}

void resolver(int Nxx, string archivo){
	int D = 1;
	int s = 1;
	int Nx = Nxx;
	int Nt = Ntt;
	// Ntc = 450 para Nx = 30
	float t_actual = 0.0;
	float t_fin = 1.0;
	float x_izq = -1.0;
	float x_der = 1.0;
	float chi_izq = 0.0;
	float chi_der = 0.0;
	float delta_t = (t_fin-t_actual)/Nt;
	float delta_x = (x_der-x_izq)/Nx;
	float chi_n[Nx];
	float chi_n_plus_1[Nx];

	ofstream outfile;
	outfile.open(archivo);

	// Este for establece la condicion inicial
	for(int i=0; i < Nx; i++){
		if(i==0) {
			chi_n[i] = chi_izq;
			chi_n_plus_1[i] = chi_izq;
		} else if(i==Nx-1) {
			chi_n[i] = chi_der;
			chi_n_plus_1[i] = chi_der;
		} else {
			chi_n[i] = 0;
		}
		outfile << chi_n[i] << " ";
	}
	outfile << endl;

	// Este while resuelve la ecuacion diferencial parcial
	while(t_actual+delta_t < t_fin) {
		outfile << chi_n_plus_1[0] << " ";
		for(int i = 1; i < Nx-1; i++){
			chi_n_plus_1[i] = chi_n[i] + D*delta_t/(delta_x*delta_x)*(chi_n[i+1]-2*chi_n[i]+chi_n[i-1]) + delta_t*s; 
			outfile << chi_n_plus_1[i] << " ";
		}
		outfile << chi_n_plus_1[Nx-1] << " ";
		outfile << endl;
		for(int i = 0; i < Nx; i++){
			chi_n[i] = chi_n_plus_1[i];
		}
		t_actual += delta_t;
	}
	outfile.close();
}