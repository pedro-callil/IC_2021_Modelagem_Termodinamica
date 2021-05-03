#include "definitions_and_headers.h"

int main ( int argc, char **argv ) {

	Metadata system_description;
	Data system;
	System data_for_fit;
	char *filename;

	if ( argc < 2 ) {
		printf ( "Usage: FitWaterActivity <filename>\n" );
		exit(1);
	}

	filename = argv[1];

	initialize ( filename, &system_description, &system );

	data_for_fit.description = system_description;
	data_for_fit.x_and_aw = system;

	fit_to_model ( &data_for_fit );

	finalize ( &system_description, &system );

	return 0;

}
