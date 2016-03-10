#include <stdio.h>
#include <stdlib.h>
#include "schrodinger.h"
#include <math.h>
#include <time.h>
#include <string.h>

#define INPUT  argv[1]
#define OUTPUT argv[2]
#define OUTPUT_xyz argv[3]

#define PI 3.1415926535
#define hbar  1 //eV*fms

#define n parameters.n
#define m parameters.m
#define L parameters.L
#define e parameters.e
#define K parameters.K
#define O parameters.O
#define N parameters.N
#define dt parameters.dt
#define S parameters.t
#define s_out parameters.s_out
#define s_xyz parameters.s_xyz

int main(int argc, char *argv[]){


FILE *output_file; // file containg t,H,V,T,P
FILE *output_xyz_file; // file containg x y z coordinates
output_xyz_file=fopen(OUTPUT_xyz,"w");
output_file=fopen(OUTPUT,"w");

struct Parameters parameters; // struct containg parameters
loadData(INPUT,&parameters); // loading input parameters

printf("n:  %lf \n",n);
printf("m:  %lf \n",m);
printf("L:  %lf \n",L);
printf("e:  %lf \n",e);
printf("K:  %lf \n",K);
O*=3*PI*PI/2;
printf("omega:  %lf \n",O);
printf("N:  %d \n",N);
printf("dt:  %lf \n",dt);
printf("t:  %d \n",S);
printf("s_out:  %d \n",s_out);
printf("s_xyz:  %d \n",s_xyz);

double dx = (double)L/N;
double t=0;

printf("dt:  %lf \n",dt);
printf("dx:  %lf \n",dx);
printf("EPS: %lf \n", dt/dx/dx);

//getchar();

double E_tot=0;
double X_=0;
double N_=0;
double* R_Psi = (double*)calloc(N+1,sizeof(double*));
double* I_Psi = (double*)calloc(N+1,sizeof(double*));
double* x_k = (double*)calloc(N+1,sizeof(double*));
double* H_R = (double*)calloc(N+1,sizeof(double*));
double* H_I = (double*)calloc(N+1,sizeof(double*));

for(int ii=0;ii<N+1;ii++){
		x_k[ii]=dx*ii;
		R_Psi[ii]=sqrt(2)*sin(n*PI*x_k[ii]);
		I_Psi[ii]=0;
	}

	
	for(int ii=1;ii<N;ii++){
		H_R[ii]=H(R_Psi,x_k,dx,ii,K,O,0);
		H_I[ii]=H(I_Psi,x_k,dx,ii,K,O,0);
	}
	H_R[0]=0;
	H_I[0]=0;
	H_R[N]=0;
	H_I[N]=0;


//inicjalizacja funkcji falowej
//koniec inicjalizacji
//zapis funkcji falowej do pliku

for(int i=0;i<S;i++){

  if(i%s_xyz==0){
    for(int ii=0;ii<N;ii++) fprintf(output_xyz_file,"%lf\t%lf\n",R_Psi[ii],I_Psi[ii]);
  }
  
  if(i%s_out==0){
  	E_tot=0;
		X_=0;
		N_=0;
		for(int ii=0;ii<N+1;ii++) E_tot+=R_Psi[ii]*H_R[ii]+I_Psi[ii]*H_I[ii];
		for(int ii=0;ii<N+1;ii++) N_+=(R_Psi[ii]*R_Psi[ii])+(I_Psi[ii]*I_Psi[ii]);
		for(int ii=0;ii<N+1;ii++) X_+=x_k[ii]*((R_Psi[ii]*R_Psi[ii])+(I_Psi[ii]*I_Psi[ii]));
		fprintf(output_file, "%lf\t%lf\t%lf\t%lf\n",t,E_tot*dx,X_*dx,N_*dx);
  }

  	for(int ii=0;ii<N+1;ii++) R_Psi[ii]+=H_I[ii]*dt/2;
	for(int ii=1;ii<N;ii++) H_R[ii]=H(R_Psi,x_k,dx,ii,K,O,t+dt/2);
	for(int ii=0;ii<N+1;ii++) I_Psi[ii]-=H_R[ii]*dt;
	for(int ii=1;ii<N;ii++) H_I[ii]=H(I_Psi,x_k,dx,ii,K,O,t+dt);
	for(int ii=0;ii<N+1;ii++) R_Psi[ii]+=H_I[ii]*dt/2;
	for(int ii=1;ii<N;ii++) H_R[ii]=H(R_Psi,x_k,dx,ii,K,O,t+dt);
  

t+=dt;

}

//fprintf(output_xyz_file,"%d\t%lf\n",N,Tau);



free(I_Psi);
free(R_Psi);
free(x_k);
free(H_R);
free(H_I);
fclose(output_xyz_file);
fclose(output_file);



return 0;

}
