#include "definitions_and_headers.h"

double get_R_squared ( gsl_multifit_nlinear_workspace *w, System *data ) {

	int i, j, n, p;
	double aw, xw, phi_real;
	double avg_phi_real, SSres, SStot, R_squared;
	gsl_vector *errors;

	n = data->description.dataset_size;
	p = data->description.n_of_comps;

	errors = gsl_vector_alloc (n);

	w->fdf->f ( w->x, (void *) data, errors );

	avg_phi_real = 0;
	for ( i = 0; i < n; i++ ) {
		aw = data->x_and_aw.aw[i];
		xw = 1;
		for ( j = 0; j < p; j++ ) {
			xw -= data->x_and_aw.x[i][j];
		}
		avg_phi_real += log (aw) / log (xw);
	}
	avg_phi_real = avg_phi_real / n;
	SStot = 0;
	SSres = 0;
	for ( i = 0; i < n; i++ ) {
		aw = data->x_and_aw.aw[i];
		xw = 1;
		for ( j = 0; j < p; j++ ) {
			xw -= data->x_and_aw.x[i][j];
		}
		phi_real = log (aw) / log (xw);
		SStot += pow ( gsl_vector_get ( errors, i )
				+ phi_real - avg_phi_real, 2 );
		SSres += pow ( gsl_vector_get ( errors, i ), 2 );
	}

	R_squared = 1 - ( SSres / SStot );

	gsl_vector_free (errors);

	return R_squared;
}

double get_R_squared_check ( double *errors, System *data ) {

	int i, j, n, p;
	double aw, xw, phi_real;
	double avg_phi_real, SSres, SStot, R_squared;

	n = data->description.dataset_size;
	p = data->description.n_of_comps;

	avg_phi_real = 0;
	for ( i = 0; i < n; i++ ) {
		aw = data->x_and_aw.aw[i];
		xw = 1;
		for ( j = 0; j < p; j++ ) {
			xw -= data->x_and_aw.x[i][j];
		}
		avg_phi_real += log (aw) / log (xw);
	}
	avg_phi_real = avg_phi_real / n;
	SStot = 0;
	SSres = 0;
	for ( i = 0; i < n; i++ ) {
		aw = data->x_and_aw.aw[i];
		xw = 1;
		for ( j = 0; j < p; j++ ) {
			xw -= data->x_and_aw.x[i][j];
		}
		phi_real = log (aw) / log (xw);
		SStot += pow ( errors[i] + phi_real - avg_phi_real, 2 );
		SSres += pow ( errors[i], 2 );
	}

	R_squared = 1 - ( SSres / SStot );

	return R_squared;
}
