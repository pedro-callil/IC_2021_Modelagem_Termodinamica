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

	fit_to_model ( &data_for_fit, user_data );

	finalize ( &system_description, &system, &user_data );

	return 0;

}
