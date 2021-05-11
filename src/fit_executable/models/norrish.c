#include "../definitions_and_headers.h"

/* This function is an implementation of Norrish's model for predicting water
 * activity in solutions, to be used for fitting.
 */

int phi_norrish ( const gsl_vector *K, void *params, gsl_vector * f ) {

	System *data;
	double phi_i_calc, phi_i_real;
	double xw, sumxiki;
	int n, c;
	int i, j;

	data = (System *) params;

	n = data->description.dataset_size;
	c = data->description.n_of_comps;

	for ( i = 0; i < n; i++ ) {
		xw = 1;
		sumxiki = 0;
		for ( j = 0; j < c; j++ ) {
			xw -= data->x_and_aw.x[i][j];
			sumxiki += gsl_vector_get ( K, j ) * data->x_and_aw.x[i][j];
		}
		sumxiki = sumxiki * sumxiki;
		xw = log(xw);
		phi_i_calc = ( xw + sumxiki ) / xw;
		phi_i_real = log ( data->x_and_aw.aw[i] ) / xw;
		gsl_vector_set ( f, i, phi_i_calc - phi_i_real );
	}

	return GSL_SUCCESS;
}


void callback_norrish ( const size_t iter, void *params,
		const gsl_multifit_nlinear_workspace *w ) {

	gsl_vector *f = gsl_multifit_nlinear_residual (w);
	gsl_vector *x = gsl_multifit_nlinear_position (w);
	size_t size, i;

	fprintf ( stderr, "Iteration number %2zu:\n", iter );
	fprintf ( stderr, "\t|f(x)| = %.4f\n", gsl_blas_dnrm2 (f) );
	size = x->size;
	for ( i = 0; i < size; i++ ) {
		fprintf ( stderr, "\tK_%ld = %.4f\n", i,
				gsl_vector_get ( x, i ) );
	}
	fprintf ( stderr, "\n" );

}

void print_norrish ( gsl_matrix *covar, gsl_multifit_nlinear_workspace *w,
		int status, double chisq0, double chisq, System *data ) {

	int p, n;
	size_t i;
	double correction;

	p = data->description.n_of_comps;
	n = data->description.dataset_size;

	correction = GSL_MAX_DBL ( 1, sqrt ( chisq / (n - p) ) );

	fprintf ( stdout, "Results Obtained:\n" );
	for ( i = 0; i < p; i++ ) {
		fprintf ( stdout, "\tK_%ld = %.5e\t+/-\t%.5e\t", i,
			gsl_vector_get ( w->x, i),
			correction * sqrt ( gsl_matrix_get ( covar, i, i ) ) );
		fprintf ( stdout, "(%s)\n", data->description.components[i] );
	}
	fprintf ( stdout, "initial cost: |f(x)| = %f\n", sqrt (chisq0) );
	fprintf ( stdout, "final cost:   |f(x)| = %f\n", sqrt (chisq) );
	fprintf ( stdout, "Exit status is \"%s\".\n\n", gsl_strerror (status) );

}

