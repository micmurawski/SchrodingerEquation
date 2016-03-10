#ifndef _schrodinger_h_
#define _schrodinger_h_
#include <stdio.h>

struct Parameters{

	double n;
	double m;
	double L;
	double e;
	double K;
	double O;
	int N;
	double dt;
	int t;
	int s_out;
	int s_xyz;
};

extern void loadData(char *input_file_name,struct Parameters *p);
extern double H(double *psi,double *x_k,double dx, int i,double k,double o,double t);

#endif