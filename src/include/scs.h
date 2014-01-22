#ifndef scs_H_GUARD                                                              
#define scs_H_GUARD

// redefine printfs and memory allocators as needed
#ifdef MATLAB_MEX_FILE
  #include "mex.h"
  #define scs_printf   mexPrintf
  #define scs_free     mxFree
  #define scs_malloc   mxMalloc
  #define scs_calloc   mxCalloc
#elif defined PYTHON
  #include <Python.h>
  #include <stdlib.h>
  #define scs_printf   PySys_WriteStdout
  #define scs_free     free
  #define scs_malloc   malloc
  #define scs_calloc   calloc
#else
  #include <stdio.h>
  #include <stdlib.h>
  #define scs_printf   printf
  #define scs_free     free
  #define scs_malloc   malloc
  #define scs_calloc   calloc
#endif


/* struct that containing standard problem data */
typedef struct PROBLEM_DATA {
  int n, m; /* problem dimensions */
  /* problem data, A, b, c: */
  double * Ax;
  int * Ai, * Ap;
  int Anz;
  double * b, * c;
  int MAX_ITERS;
  double EPS_ABS, ALPH, UNDET_TOL, RHO_X;
  int VERBOSE, NORMALIZE;  // boolean
} Data;

/* contains primal-dual solution vectors */
typedef struct SOL_VARS {
  double * x, * y, *s;
} Sol;

/* contains terminating information */
typedef struct INFO {
	int iter;
	char status[16];
	int stint; // status as int
    double pobj;
	double dobj;
	double resPri;
	double resDual;
	double relGap;
	double time;
} Info;

/* not needed by user */
typedef struct PRIVATE_DATA Priv;

typedef struct WORK {
  double *u, *v, *u_t, *u_prev;
  double *h, *g;  
  double gTh, sc_b, sc_c, scale;
  double nm_b, nm_c, nm_Q;
  double *D, *E;
  Priv * p;
  int l;
  char * method;
} Work;

// to hold residual information
struct residuals {
	double resDual;
	double resPri;
    double relGap;
    double cTx;
    double bTy;
    double tau;
	double kap;
};

#include <string.h>    
#include <sys/time.h>
#include <math.h>
#include "cones.h"
#include "linAlg.h"
#include "util.h"

// these are actually library "api"'s
int scs(Data * d, Cone * k, Sol * sol, Info * info);
void freeData(Data *d, Cone *k);
void freeSol(Sol *sol);
void printSol(Data * d, Sol * sol, Info * info);
#endif
