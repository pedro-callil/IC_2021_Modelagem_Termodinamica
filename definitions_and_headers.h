#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_multifit_nlinear.h>

#define TRUE 1
#define FALSE 0

typedef struct {
	int dataset_size;
	int n_of_comps;
	char **components;
} Metadata;

typedef struct {
	double *aw;
	double **x;
} Data;

typedef struct {
	Metadata description;
	Data x_and_aw;
} System;

extern void initialize ( char *filename,
		Metadata *system_description, Data *system );
extern void finalize ( Metadata *system_description, Data *system );
extern int phi_norrish ( const gsl_vector *K, void *params, gsl_vector *f );
extern int fit_to_model ( System *data );

