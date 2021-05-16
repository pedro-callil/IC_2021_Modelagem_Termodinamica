#include "../definitions_and_headers.h"

/*
 * This function compares the values of phi predicted with Raoult's model
 * with the values of phi experimentally obtained.
 *     phi, here, is constant and equals 1; phi = ln(aw_raoult)/ln(xw) =
 * ln(xw)/ln(xw) = 1.
 */
void check_raoult ( System *data, info *user_data, double *errors ) {

	int i, j, n, p;
	double xw;

	n = data->description.dataset_size;
	p = data->description.n_of_comps;

	for ( i = 0; i < n; i++ ) {
		xw = 1;
		for ( j = 0; j < p; j++ ) {
			xw -= data->x_and_aw.x[i][j];
		}
		errors[i] = fabs ( 1 - ( log(data->x_and_aw.aw[i]) / log(xw) ) );
	}
}

void print_raoult ( System *data, info *user_data, double *errors ) {

	int i, n;

	n = data->description.dataset_size;

	user_data->cost = 0;
	for ( i = 0; i < n; i++ ) {
		user_data->cost += pow ( errors[i], 2 );
	}

	user_data->cost = sqrt (user_data->cost);

	fprintf ( stderr, "final cost:   |f(x)| = %f\n", user_data->cost );

}
