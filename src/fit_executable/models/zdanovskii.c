#include "../definitions_and_headers.h"

double x_to_m ( double x, double xw );
double aw_to_m_1st ( double aw, double *coefs );
double aw_to_m_2nd ( double aw, double *coefs );
double m_1st_to_aw ( double m_1st, double *coefs );
double polynomial ( double x, double *coefs );
void fit_polynomial ( double *x_data, double *y_data,
		double *coefs, int size );

/*
 * This function compares the water activities with the values
 * predicted using zdanovskii's relation
 */
void check_zdanovskii ( System *data, info *user_data, double *errors ) {

	int i, j, n, p;
	double xw, aw, m_1, m_2, m_01, m_02, phi_calc, phi_real, S;
	double *m_1st_vec, *m_2nd_vec, *aw_vec;
	double K_aw_to_m_1st[DEG_POLY_ZDAN];
	double K_aw_to_m_2nd[DEG_POLY_ZDAN];
	double K_m_1st_to_aw[DEG_POLY_ZDAN];

	n = data->description.dataset_size;
	p = data->description.n_of_comps;

	/* allocating memory for molalities and water activities */
	m_1st_vec = malloc ( n * sizeof (double) );
	m_2nd_vec = malloc ( n * sizeof (double) );
	aw_vec = malloc ( n * sizeof (double) );

	/* converting data from mol fraction to molality */
	for ( i = 0; i < n; i++ ) {
		xw = 1;
		for ( j = 0; j < p; j++ ) {
			xw -= data->x_and_aw.x[i][j];
		}
		m_1st_vec[i] = x_to_m ( data->x_and_aw.x[i][0], xw );
		m_2nd_vec[i] = x_to_m ( data->x_and_aw.x[i][1], xw );
		aw_vec[i] = data->x_and_aw.aw[i];
	}

	/* get relations between molality and water activity */
	fit_polynomial ( m_1st_vec, aw_vec, K_m_1st_to_aw, n );
	fit_polynomial ( aw_vec, m_1st_vec, K_aw_to_m_1st, n );
	fit_polynomial ( aw_vec, m_2nd_vec, K_aw_to_m_2nd, n );

	/* apply zdanovskii model */
	for ( i = 0; i < n; i++ ) {
		xw = 1;
		for ( j = 0; j < p; j++ ) {
			xw -= data->x_and_aw.x[i][j];
		}
		aw = xw; /* Using Raoult as initial guess */

		m_01 = aw_to_m_1st ( aw, K_aw_to_m_1st );
		m_02 = aw_to_m_2nd ( aw, K_aw_to_m_2nd );
		m_1 = x_to_m ( data->x_and_aw.x[i][0], xw );
		m_2 = x_to_m ( data->x_and_aw.x[i][1], xw );
		S = ( m_1 / m_01 ) + ( m_2 / m_02 );

		while ( fabs ( S - 1 ) < TOL_ZDAN ) {
			m_01 = S * m_01;
			aw = m_1st_to_aw ( m_01, K_m_1st_to_aw );
			m_02 = aw_to_m_2nd ( aw, K_aw_to_m_2nd );
			S = ( m_1 / m_01 ) + ( m_2 / m_02 );
		}

		aw = m_1st_to_aw ( m_01, K_m_1st_to_aw );
		phi_real = log (data->x_and_aw.aw[i]) / log (xw);
		phi_calc = log (aw) / log (xw);
		errors[i] = fabs ( phi_real - phi_calc );
	}

	free (m_1st_vec);
	free (m_2nd_vec);
	free (aw_vec);
}

void print_zdanovskii ( System *data, info *user_data, double *errors ) {

	int i, n;

	n = data->description.dataset_size;

	user_data->cost = 0;
	for ( i = 0; i < n; i++ ) {
		user_data->cost += pow ( errors[i], 2 );
	}

	user_data->cost = sqrt (user_data->cost);

	if ( user_data->is_all == FALSE ) {
		fprintf ( stderr, "final cost:   |f(x)| = %f\n", user_data->cost );
	}

}

/* this is the polynomial as needed for GSL non-linear fitting */
int polynomial_as_gsl ( const gsl_vector *K, void *params, gsl_vector *f ) {

	int size, i, j;
	double real, calc;
	struct_for_zdan *data;

	data = (struct_for_zdan *) params;
	size = data->size;

	for ( i = 0; i < size; i++ ) {
		calc = 0;
		for ( j = 0; j < DEG_POLY_ZDAN; j++ ) {
			calc += gsl_vector_get ( K, j ) *
				pow ( data->x[i], j );
		}
		real = data->y[i];
		gsl_vector_set ( f, i, real - calc );
	}

	return GSL_SUCCESS;
}

/* get polynomial coeficients from data  */
void fit_polynomial ( double *x_data, double *y_data,
		double *coefs, int size ) {

	int i, n, info;
	const gsl_multifit_nlinear_type *T = gsl_multifit_nlinear_trust;
	gsl_multifit_nlinear_workspace *w;
	gsl_multifit_nlinear_fdf fdf;
	gsl_multifit_nlinear_parameters fdf_params =
		gsl_multifit_nlinear_default_parameters ();
	gsl_vector_view x;
	callback_function callback;
	double x_init[DEG_POLY_ZDAN];
	const double xtol = 1e-9;
	const double gtol = 1e-9;
	const double ftol = 0;
	struct_for_zdan data_for_func;

	data_for_func.size = size;
	data_for_func.x = x_data;
	data_for_func.y = y_data;

	n = size;
	fdf.f = polynomial_as_gsl;
	fdf.df = NULL;
	fdf.fvv = NULL;
	callback = NULL;
	fdf.n = n;
	fdf.p = DEG_POLY_ZDAN;
	fdf.params = &data_for_func;

	x_init[0] = 1;
	for ( i = 1; i < DEG_POLY_ZDAN; i++ ) {
		x_init[i] = 0;
	}
	x = gsl_vector_view_array ( x_init, DEG_POLY_ZDAN );
	w = gsl_multifit_nlinear_alloc ( T, &fdf_params, n, DEG_POLY_ZDAN );
	gsl_multifit_nlinear_winit ( &x.vector, NULL, &fdf, w );

	gsl_multifit_nlinear_driver ( 100, xtol, gtol, ftol,
			callback, NULL, &info, w);

	for ( i = 0; i < DEG_POLY_ZDAN; i++ ) {
		coefs[i] = gsl_vector_get ( w->x, i );
	}

	gsl_multifit_nlinear_free (w);

}


/* auxiliary functions for property conversion */
double x_to_m ( double x, double xw ) {

	return x / ( xw * KGS_IN_MOL_WATER );

}

double polynomial ( double x, double *coefs ) {

	int i;
	double y = 0;

	for ( i = 0; i < DEG_POLY_ZDAN; i++ ) {
		y += coefs[i] * pow ( x, i );
	}

	return y;
}

double aw_to_m_1st ( double aw, double *coefs ) {

	double m_1st;

	m_1st = polynomial ( aw, coefs );

	return m_1st;

}

double aw_to_m_2nd ( double aw, double *coefs ) {

	double m_2nd;

	m_2nd = polynomial ( aw, coefs );

	return m_2nd;

}

double m_1st_to_aw ( double m_1st, double *coefs ) {

	double aw;

	aw = polynomial ( m_1st, coefs );

	return aw;

}
