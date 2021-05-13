#include "definitions_and_headers.h"

/*
 * This function performs an analysis of non-parametric models, as
 * Raoult's, Caurie's or Zdanovskii's.
 */

int check_model ( System *data, info *user_data ) {

	check_function check;
	print_function_for_check print;
	int n;
	double *errors;

	n = data->description.dataset_size;
	errors = malloc ( n * sizeof (double) );
	/* array in which the absolute values
	* of the errors shall be stored
	*/

	if ( strcmp ( user_data->model, "raoult" ) == TRUE ) {
		check = &check_raoult;
		print = &print_raoult;
	} else if ( strcmp ( user_data->model, "caurie" ) ==TRUE ) {
		check = &check_caurie;
		print = &print_caurie;
	} else {
		fprintf ( stderr, "Model unknown. Assuming Raoult's Law.\n" );
		check = &check_raoult;
		print = &print_raoult;
	}

	check ( data, user_data, errors );
	print ( data, user_data, errors );

	free (errors);

	return 0;
}

