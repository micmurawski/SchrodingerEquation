#include "schrodinger.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

inline void loadData(char *input_file_name,struct Parameters *p){

   FILE *input_file;

   input_file=fopen(input_file_name,"r");
  
    if( input_file == NULL )
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
 
   fscanf(input_file, "%lf,",&p->n);  //1
   fscanf(input_file, "%lf,",&p->m); //2
   fscanf(input_file, "%lf,",&p->L); //3
   fscanf(input_file, "%lf,",&p->e); //4
   fscanf(input_file, "%lf,",&p->K); //5
   fscanf(input_file, "%lf,",&p->O); //6
   fscanf(input_file, "%d,",&p->N);
   fscanf(input_file, "%lf,",&p->dt);
   fscanf(input_file, "%d,",&p->t);
   fscanf(input_file, "%d,",&p->s_out);
   fscanf(input_file, "%d,",&p->s_xyz);

   fclose(input_file);
   
   }


inline double H(double *psi,double *x_k,double dx, int i,double k,double o,double t){
  double P=(-0.5*(psi[i+1]+psi[i-1]-2*psi[i])/pow(dx,2))+k*(x_k[i]-0.5)*psi[i]*sin(o*t);
  return  P;
}