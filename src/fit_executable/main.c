#include "definitions_and_headers.h"

int main ( int argc, char **argv ) {

	Metadata system_description;
	Data system;
	System data_for_fit;
	info user_data;

	getargs ( argc, argv, &user_data );
	/* read command line arguments from user */

	initialize ( user_data.filename, &system_description, &system );
	/* read file to data structure and malloc required blocks */

	data_for_fit.description = system_description;
	data_for_fit.x_and_aw = system;

	if ( strcmp ( user_data.model, "norrish" ) == TRUE ||
			strcmp ( user_data.model, "virial" ) == TRUE ) {
		fit_to_model ( &data_for_fit, &user_data );
		/* if the model choosen requires non-linear fitting */
	} else if ( strcmp ( user_data.model, "raoult" ) == TRUE ||
			strcmp ( user_data.model, "caurie" ) == TRUE ||
			strcmp ( user_data.model, "zdanovskii" ) == TRUE ) {
		check_model ( &data_for_fit, &user_data );
		/* otherwise */
	}

	finalize ( &system_description, &system, &user_data );
	/* free remaining malloc'd blocks */

	return 0;

}