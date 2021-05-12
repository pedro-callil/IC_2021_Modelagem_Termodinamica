#include "definitions_and_headers.h"

int main ( int argc, char **argv ) {

	Metadata system_description;
	Data system;
	System data_for_fit;
	info user_data;

	getargs ( argc, argv, &user_data );

	initialize ( user_data.filename, &system_description, &system );

	data_for_fit.description = system_description;
	data_for_fit.x_and_aw = system;

	if ( strcmp ( user_data.model, "norrish" ) == TRUE ||
			strcmp ( user_data.model, "virial" ) == TRUE ||
			strcmp ( user_data.model, "uniquac" ) == TRUE ) {
		fit_to_model ( &data_for_fit, user_data );
	} else if ( strcmp ( user_data.model, "raoult" ) == TRUE ||
			strcmp ( user_data.model, "caurie" ) == TRUE ||
			strcmp ( user_data.model, "zdanovskii" ) == TRUE ) {
		check_model ( &data_for_fit, user_data );
	}

	finalize ( &system_description, &system, &user_data );

	return 0;

}
