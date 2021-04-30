#include "definitions_and_headers.h"

int main ( int argc, char **argv ) {

	Metadata system_description;
	Data system;
	char *filename;

	if ( argc < 2 ) {
		printf ( "Usage: FitWaterActivity <filename>\n" );
		exit(1);
	}

	filename = argv[1];

	initialize ( filename, &system_description, &system );

	finalize ( &system_description, &system );

	return 0;

}
