#include "definitions_and_headers.h"

/*
 * NOTICE:
 *
 *
 * A significant portion of this file was adapted from the examples provided in
 * the GNU Scientific Library Reference Manual.
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

int fit_to_model ( System *data ) {

	size_t n, p, i;
	const gsl_multifit_nlinear_type *T = gsl_multifit_nlinear_trust;
	gsl_multifit_nlinear_workspace *w;
	gsl_multifit_nlinear_fdf fdf;
	gsl_multifit_nlinear_parameters fdf_params =
		gsl_multifit_nlinear_default_parameters ();
	gsl_vector *f;
	gsl_matrix *J, *covar;
	gsl_vector_view x;
	const double xtol = 1e-5;
	const double gtol = 1e-5;
	const double ftol = 0.0;
	double *x_init;
	double chisq, chisq0, correction;
	int status, info;

	n = data->description.dataset_size;
	p = data->description.n_of_comps;

	fdf.f = phi_norrish;
	fdf.df = NULL;
	fdf.fvv = NULL;
	fdf.n = n;
	fdf.p = p;
	fdf.params = data;

	covar = gsl_matrix_alloc ( p, p );
	x_init = malloc ( p * sizeof (double) );
	for ( i = 0; i < p; i++ ) {
		x_init[i] = 1;
	}
	x = gsl_vector_view_array ( x_init, p );

	w = gsl_multifit_nlinear_alloc ( T, &fdf_params, n, p );
	gsl_multifit_nlinear_winit ( &x.vector, NULL, &fdf, w );

	f = gsl_multifit_nlinear_residual (w);
	gsl_blas_ddot ( f, f, &chisq0 );

	status = gsl_multifit_nlinear_driver ( 100, xtol, gtol, ftol,
			callback_norrish, NULL, &info, w);

	J = gsl_multifit_nlinear_jac (w);
	gsl_multifit_nlinear_covar ( J, 0.0, covar );

	gsl_blas_ddot ( f, f, &chisq );
	correction = GSL_MAX_DBL ( 1, sqrt ( chisq / (n - p) ) );

	fprintf ( stderr, "Results Obtained:\n" );
	for ( i = 0; i < p; i++ ) {
		fprintf ( stderr, "\tK_%ld = %.5f +/- %.5f\n", i,
				gsl_vector_get ( w->x, i),
				correction * sqrt ( gsl_matrix_get ( covar, i, i ) ) );
	}
	fprintf ( stderr, "initial cost: |f(x)| = %f\n", sqrt (chisq0) );
	fprintf ( stderr, "final cost:   |f(x)| = %f\n", sqrt (chisq) );
	fprintf ( stderr, "Exit status is \"%s\".\n\n", gsl_strerror (status) );

	gsl_multifit_nlinear_free (w) ;
	gsl_matrix_free (covar);
	free (x_init);

	return 0;
}

