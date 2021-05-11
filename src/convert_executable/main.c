#include "definitions_and_headers.h"

int main ( int argc, char **argv ) {

	Metadata system_description;
	Data system, new_system;
	info user_data;

	getargs ( argc, argv, &user_data );

	initialize ( user_data.filename, &system_description, &system );

	new_system = convert ( &system_description, &system, &user_data );

	write_to_file ( &system_description, &new_system, &user_data );

	finalize ( &system_description, &new_system, &system, &user_data );

	return 0;

}
