#include "../definitions_and_headers.h"

double x_to_m ( double x, double xw );
double aw_to_m_1st ( double aw, double *coefs, int degree );
double aw_to_m_2nd ( double aw, double *coefs, int degree );
double m_1st_to_aw ( double m_1st, double *coefs, int degree );
double polynomial ( double x, double *coefs, int degree );
void fit_polynomial ( double *x_data, double *y_data,
		double *coefs, int size, int degree );

/*
 * This function compares the water activities with the values
 * predicted using zdanovskii's relation
 */
void check_zdanovskii ( System *data, info *user_data, double *errors ) {

	int i, j, n, p, iter, degree_01, degree_02;
	double xw, aw, m_1, m_2, m_01, m_02, phi_calc, phi_real, S;
	double *m_1st_vec, *m_2nd_vec, *aw_vec;
	double *m_01_std, *m_02_std, *aw_01_std, *aw_02_std;
	double *K_aw_to_m_1st;
	double *K_aw_to_m_2nd;
	double *K_m_1st_to_aw;

	n = data->description.dataset_size;
	p = data->description.n_of_comps;

	/* allocating memory for molalities and water activities */
	m_1st_vec = malloc ( n * sizeof (double) );
	m_2nd_vec = malloc ( n * sizeof (double) );
	aw_vec = malloc ( n * sizeof (double) );

	m_01_std = malloc ( data->x_and_aw.n_zdan[0] * sizeof (double) );
	aw_01_std = malloc ( data->x_and_aw.n_zdan[0] * sizeof (double) );

	for ( i = 0; i < data->x_and_aw.n_zdan[0]; i++ ) {
		m_01_std[i] = x_to_m ( data->x_and_aw.x_zdan[0][i],
				1 - data->x_and_aw.x_zdan[0][i] );
		aw_01_std[i] = data->x_and_aw.aw_zdan[0][i];
	}

	m_02_std = malloc ( data->x_and_aw.n_zdan[1] * sizeof (double) );
	aw_02_std = malloc ( data->x_and_aw.n_zdan[1] * sizeof (double) );

	for ( i = 0; i < data->x_and_aw.n_zdan[1]; i++ ) {
		m_02_std[i] = x_to_m ( data->x_and_aw.x_zdan[1][i],
				1 - data->x_and_aw.x_zdan[1][i] );
		aw_02_std[i] = data->x_and_aw.aw_zdan[1][i];
	}

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

	if ( data->x_and_aw.n_zdan[0] < 10 ) {
		degree_01 = (int) sqrt (data->x_and_aw.n_zdan[0] );
	} else {
		degree_01 = DEG_POLY_ZDAN;
	}

	if ( data->x_and_aw.n_zdan[1] < 10 ) {
		degree_02 = (int) sqrt (data->x_and_aw.n_zdan[0] );
	} else {
		degree_02 = DEG_POLY_ZDAN;
	}

	K_m_1st_to_aw = malloc ( degree_01 * sizeof (double) );
	K_aw_to_m_1st = malloc ( degree_01 * sizeof (double) );
	K_aw_to_m_2nd = malloc ( degree_02 * sizeof (double) );

	fit_polynomial ( m_01_std, aw_01_std, K_m_1st_to_aw,
			data->x_and_aw.n_zdan[0], degree_01 );
	fit_polynomial ( aw_01_std, m_01_std, K_aw_to_m_1st,
			data->x_and_aw.n_zdan[0], degree_01 );
	fit_polynomial ( aw_02_std, m_02_std, K_aw_to_m_2nd,
			data->x_and_aw.n_zdan[1], degree_02 );

	/* apply zdanovskii model */
	for ( i = 0; i < n; i++ ) {
		xw = 1;
		for ( j = 0; j < p; j++ ) {
			xw -= data->x_and_aw.x[i][j];
		}
		aw = xw; /* Using Raoult as initial guess */

		m_01 = aw_to_m_1st ( aw, K_aw_to_m_1st, degree_01 );
		m_02 = aw_to_m_2nd ( aw, K_aw_to_m_2nd, degree_02 );
		m_1 = x_to_m ( data->x_and_aw.x[i][0], xw );
		m_2 = x_to_m ( data->x_and_aw.x[i][1], xw );
		S = ( m_1 / m_01 ) + ( m_2 / m_02 );

		iter = 0;
		while ( fabs ( S - 1 ) < TOL_ZDAN ) {
			m_01 = S * m_01;
			aw = m_1st_to_aw ( m_01, K_m_1st_to_aw, degree_01 );
			m_02 = aw_to_m_2nd ( aw, K_aw_to_m_2nd, degree_02 );
			S = ( m_1 / m_01 ) + ( m_2 / m_02 );
			iter ++;
			if ( iter >= MAX_ITER_ZDAN ) {
				fprintf ( stderr,
					"Maximum number of iterations (%d) ",
					MAX_ITER_ZDAN );
				fprintf ( stderr,
					"now surpassed. Aborting...\n" );
				exit (39);
			}
		}

		aw = m_1st_to_aw ( m_01, K_m_1st_to_aw, degree_01 );
		phi_real = log (data->x_and_aw.aw[i]) / log (xw);
		phi_calc = log (aw) / log (xw);
		errors[i] = fabs ( phi_real - phi_calc );
	}

	free (m_1st_vec);
	free (m_2nd_vec);
	free (aw_vec);

	free (m_01_std);
	free (aw_01_std);
	free (m_02_std);
	free (aw_02_std);

	free (K_m_1st_to_aw);
	free (K_aw_to_m_1st);
	free (K_aw_to_m_2nd);
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

	int size, degree, i, j;
	double real, calc;
	struct_for_zdan *data;

	data = (struct_for_zdan *) params;
	size = data->size;
	degree = data->degree;

	for ( i = 0; i < size; i++ ) {
		calc = 0;
		for ( j = 0; j < degree; j++ ) {
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
		double *coefs, int size, int degree ) {

	int i, n, info;
	const gsl_multifit_nlinear_type *T = gsl_multifit_nlinear_trust;
	gsl_multifit_nlinear_workspace *w;
	gsl_multifit_nlinear_fdf fdf;
	gsl_multifit_nlinear_parameters fdf_params =
		gsl_multifit_nlinear_default_parameters ();
	gsl_vector_view x;
	callback_function callback;
	double *x_init;
	const double xtol = 1e-9;
	const double gtol = 1e-9;
	const double ftol = 0;
	struct_for_zdan data_for_func;

	data_for_func.size = size;
	data_for_func.degree = degree;
	data_for_func.x = x_data;
	data_for_func.y = y_data;

	x_init = malloc ( data_for_func.degree * sizeof (double) );

	n = size;
	fdf.f = polynomial_as_gsl;
	fdf.df = NULL;
	fdf.fvv = NULL;
	callback = NULL;
	fdf.n = n;
	fdf.p = data_for_func.degree;
	fdf.params = &data_for_func;

	x_init[0] = 1;
	for ( i = 1; i < data_for_func.degree; i++ ) {
		x_init[i] = 0;
	}
	x = gsl_vector_view_array ( x_init, data_for_func.degree );
	w = gsl_multifit_nlinear_alloc ( T, &fdf_params, n, data_for_func.degree );
	gsl_multifit_nlinear_winit ( &x.vector, NULL, &fdf, w );

	gsl_multifit_nlinear_driver ( 100, xtol, gtol, ftol,
			callback, NULL, &info, w);

	for ( i = 0; i < data_for_func.degree; i++ ) {
		coefs[i] = gsl_vector_get ( w->x, i );
	}

	gsl_multifit_nlinear_free (w);
	free (x_init);

}


/* auxiliary functions for property conversion */
double x_to_m ( double x, double xw ) {

	return x / ( xw * KGS_IN_MOL_WATER );

}

double polynomial ( double x, double *coefs, int degree ) {

	int i;
	double y = 0;

	for ( i = 0; i < degree; i++ ) {
		y += coefs[i] * pow ( x, i );
	}

	return y;
}

double aw_to_m_1st ( double aw, double *coefs, int degree ) {

	double m_1st;

	m_1st = polynomial ( aw, coefs, degree );

	return m_1st;

}

double aw_to_m_2nd ( double aw, double *coefs, int degree ) {

	double m_2nd;

	m_2nd = polynomial ( aw, coefs, degree );

	return m_2nd;

}

double m_1st_to_aw ( double m_1st, double *coefs, int degree ) {

	double aw;

	aw = polynomial ( m_1st, coefs, degree );

	return aw;

}
