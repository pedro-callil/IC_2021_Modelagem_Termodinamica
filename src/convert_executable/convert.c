#include "definitions_and_headers.h"

Data convert ( Metadata *system_description, Data *system,
		info *user_data ) {

	Data new_system;
	double **x;
	double *aw;
	int lines, comps, i, j;

	lines = system_description->dataset_size;
	comps = system_description->n_of_comps;

	x = malloc ( lines * sizeof (double *) );
	aw = malloc ( lines * sizeof (double) );
	for ( i = 0; i < lines; i ++ ) {
		x[i] = malloc ( comps * sizeof (double) );
	}

	for ( i = 0; i < lines; i++ ) {
		aw[i] = (double) i / ( lines - 1 );
		for ( j = 0; j < comps; j++ ) {
			x[i][j] = (double) ( i + j ) / ( lines + comps - 2 );
		}
	}

	new_system.x = x;
	new_system.aw = aw;

	return new_system;
}
