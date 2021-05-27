/*
 * External libraries
 */

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

/*
 * Bool definition for more organization
 */

#define TRUE 0
#define FALSE 1

/* For molality calculations for Caurie's model */

#define KGS_IN_MOL_WATER 0.018015
#define FAC_B_CAURIE 3081.3601
#define FAC_C_CAURIE 171046.2991

/* Polynomial fitting - Zdanovskii relation */

#define DEG_POLY_ZDAN 4
#define MAX_ITER_ZDAN 1000
#define TOL_ZDAN 1e-6

/* Physical constants, used in UNIQUAC */

#define R 8.314462618
#define TEMP 298.15

/*
 * Data structures
 */

typedef struct {
	int dataset_size;
	int n_of_comps;
	char **components;
} Metadata;

typedef struct {
	double *aw;
	double **x;
	double **x_zdan;
	double **aw_zdan;
	int *n_zdan;
} Data;

typedef struct {
	Metadata description;
	Data x_and_aw;
} System;

typedef struct {
	char *model;
	char *filename;
	char **files_zdan;
	int quiet;
	double cost;
	int is_all;
	int gave_filenames;
	int not_zdan;
} info;

typedef struct {
	double *x;
	double *y;
	int size;
	int degree;
} struct_for_zdan;


/*
 * Function pointers
 */

typedef void (*callback_function)
	(const size_t iter, void *params,
	const gsl_multifit_nlinear_workspace *w);

typedef void (*print_function)
	(gsl_matrix *covar, gsl_multifit_nlinear_workspace *w,
	int status, double chisq0, double chisq,
	System *data, info *user_data);

typedef void (*check_function)
	( System *data, info *user_data, double *errors );

typedef void (*print_function_for_check)
	( System *data, info *user_data, double *errors );

typedef double (*polynomial_function)
	( double x, double *coefs, int degree );

/*
 * Functions and subroutines
 */

extern void getargs ( int argc, char **argv, info *user_data );
extern void initialize ( char *filename, Metadata *system_description,
		Data *system, info *user_data );
extern void init_data ( char *model, double *x_init, int p );
extern void finalize ( Metadata *system_description, Data *system,
		info *user_data );
extern int fit_to_model ( System *data, info *user_data );
extern int check_model ( System *data, info *user_data );
extern void analyze_all_models ( System *data, info *user_data );

/*
 * * * Functions specific to each model.
 */

extern int phi_norrish ( const gsl_vector *K, void *params, gsl_vector *f );
extern void callback_norrish ( const size_t iter, void *params,
		const gsl_multifit_nlinear_workspace *w );
extern void print_norrish ( gsl_matrix *covar,
		gsl_multifit_nlinear_workspace *w, int status,
		double chisq0, double chisq,
		System *data, info *user_data );

extern int phi_virial ( const gsl_vector *K, void *params, gsl_vector *f );
extern void callback_virial ( const size_t iter, void *params,
		const gsl_multifit_nlinear_workspace *w );
extern void print_virial ( gsl_matrix *covar,
		gsl_multifit_nlinear_workspace *w, int status,
		double chisq0, double chisq,
		System *data, info *user_data );

extern int phi_uniquac ( const gsl_vector *K, void *params, gsl_vector *f );
extern void callback_uniquac ( const size_t iter, void *params,
		const gsl_multifit_nlinear_workspace *w );
extern void print_uniquac ( gsl_matrix *covar,
		gsl_multifit_nlinear_workspace *w, int status,
		double chisq0, double chisq,
		System *data, info *user_data );

extern void check_raoult ( System *data, info *user_data, double *errors );
extern void print_raoult ( System *data, info *user_data, double *errors );

extern void check_caurie ( System *data, info *user_data, double *errors );
extern void print_caurie ( System *data, info *user_data, double *errors );


extern void check_zdanovskii ( System *data, info *user_data, double *errors );
extern void print_zdanovskii ( System *data, info *user_data, double *errors );


