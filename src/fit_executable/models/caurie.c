#include "../definitions_and_headers.h"

/*
 * This function compares the values of phi predicted with Raoult's model
 * with the values of phi experimentally obtained.
 */
void check_caurie ( System *data, info *user_data, double *errors ) {

	int i, j, k, l, o, n, p;
	double xw, prod_aw, *m, phi_real, phi_calc;

	n = data->description.dataset_size;
	p = data->description.n_of_comps;

	m = malloc ( p * sizeof (double) );
	for ( i = 0; i < p; i++ ) {
		m[i] = 0;
	}

	for ( i = 0; i < n; i++ ) {
		xw = 1;
		for ( j = 0; j < p; j++ ) {
			xw -= data->x_and_aw.x[i][j];
		}
		prod_aw = 1;
		for ( j = 0; j < p; j++ ) {
			prod_aw *= xw / ( xw + data->x_and_aw.x[i][j] );
		}
		if ( p > 1 ) {
			for ( j = 0; j < p; j++ ) {
				m[j] = data->x_and_aw.x[i][j] /
					( xw * KGS_IN_MOL_WATER );
			}
			for ( k = 0; k < p; k++ ) {
				for ( l = 0; l < k; l++ ) {
					prod_aw -= ( p / FAC_B_CAURIE ) *
						m[k] * m[l];
				}
			}
			if ( p > 2 ) {
				for ( k = 0; k < p; k++ ) {
					for ( l = 0; l < k; l++ ) {
						for ( o = 0; o < l; o++ ) {
							prod_aw -=
								( ( p + 1 ) /
								FAC_C_CAURIE ) *
								m[k] * m[l] * m[o];
						}
					}
				}
			}
		}
		phi_calc = log (prod_aw) / log (xw);
		phi_real = log (data->x_and_aw.aw[i]) / log (xw);
		errors[i] = fabs ( phi_real - phi_calc );
	}

	free (m);
}

void print_caurie ( System *data, info *user_data, double *errors ) {

	int i, n;
	double cost;

	n = data->description.dataset_size;

	cost = 0;
	for ( i = 0; i < n; i++ ) {
		cost += pow ( errors[i], 2 );
	}

	fprintf ( stderr, "final cost:   |f(x)| = %f\n", sqrt (cost) );

}
