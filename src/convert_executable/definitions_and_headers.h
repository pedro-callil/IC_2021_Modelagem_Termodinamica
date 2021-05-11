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

#define KELVIN_TO_CELSIUS 273.15
#define MOLALITY_TO_FRACTION 55.51
#define MASS_TO_FRACTION 18.015

/* constants for arden_buck function */
#define A_A 6.1121
#define B_A 18.678
#define C_A 234.5
#define D_A 257.14

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
} Data;

typedef struct {
	Metadata description;
	Data x_and_aw;
} System;

typedef struct {
	char *filename;
	char *new_filename;
	char *y_property;
	double temperature;
	double temperature_to_add;
	double pressure;
	char *x_property;
	double *molar_masses;
	int quiet;
} info;

/*
 * Functions and subroutines
 */

extern void getargs ( int argc, char **argv, info *user_data );
extern void initialize ( char *filename,
		Metadata *system_description, Data *system );
extern Data convert ( Metadata *system_description, Data *system,
		info *user_data );
extern void write_to_file ( Metadata *system_description, Data *new_system,
		info *user_data );
extern void finalize ( Metadata *system_description, Data *new_system,
		Data *system, info *user_data );

