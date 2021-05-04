#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <getopt.h>
#include <unistd.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_multifit_nlinear.h>

#define TRUE 0
#define FALSE 1

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

typedef struct {
	char *model;
	char *filename;
	int quiet;
} info;

typedef void (*callback_function)
	(const size_t iter, void *params,
	const gsl_multifit_nlinear_workspace *w);

typedef void (*print_function)
	(gsl_matrix *covar, gsl_multifit_nlinear_workspace *w,
	int status, double chisq0, double chisq, System *data);

extern void getargs ( int argc, char **argv, info *user_data );
extern void initialize ( char *filename,
		Metadata *system_description, Data *system );
extern void finalize ( Metadata *system_description, Data *system,
		info *user_data );
extern int fit_to_model ( System *data, info user_data );

/*
 * Functions specific to each model.
 */

extern int phi_norrish ( const gsl_vector *K, void *params, gsl_vector *f );
extern void callback_norrish ( const size_t iter, void *params,
		const gsl_multifit_nlinear_workspace *w );
extern void print_norrish ( gsl_matrix *covar,
		gsl_multifit_nlinear_workspace *w, int status,
		double chisq0, double chisq, System *data );

