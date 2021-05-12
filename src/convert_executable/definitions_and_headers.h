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

#define R_CONST 8.31446261815324

#define FREEZING_POINT_WATER 273.15
#define DELTA_H_FUS 6010.0

/* constants for arden_buck function */
#define A_A 6.1121
#define B_A 18.678
#define C_A 234.5
#define D_A 257.14

/* constants for boiling_point function (antoine) */
#define A_B 23.195
#define B_B 3814.0
#define C_B -46.29

/* constants for specific heat of gas, liquid and solid phases */
#define A_G 33.80
#define B_G -7.95e-3
#define C_G 2.8228e-5
#define D_G -1.3115e-8

#define A_L 917.5
#define B_L -10.1016
#define C_L 0.0454134
#define D_L -9.07517e-5
#define E_L 6.80700e-8
	/*
	* Data from the CRC Handbook of Thermophysical and Thermochemical Data
	*/
#define A_S 0.750779
#define B_S -0.00304536
#define C_S 0.0000567243
#define D_S -1.0305e-7
	/*
	* Data from The Engineering Toolbox (placeholder)
	*/

/* constants for delta_h_vap function (fitted data from sandler) */

#define A_H 67631.3
#define B_H -142.57
#define C_H 0.313106
#define D_H -0.0003325

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
extern void initialize ( char *filename, Metadata *system_description,
		Data *system, info *user_data );
extern Data convert ( Metadata *system_description, Data *system,
		info *user_data );
extern void write_to_file ( Metadata *system_description, Data *new_system,
		info *user_data );
extern void finalize ( Metadata *system_description, Data *new_system,
		Data *system, info *user_data );

