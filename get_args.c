#include "definitions_and_headers.h"

void print_usage (void) {

	printf ( "Usage: FitWaterActivity [OPTIONS]\n" );
	printf ( "    Options:\n" );
	printf ( "        -h\n" );
	printf ( "          Show this help\n" );
	printf ( "        -q\n" );
	printf ( "          Quiet; hide verbose output\n" );
	printf ( "        -f <filename>\n" );
	printf ( "          File in which the activity data are stored\n" );
	printf ( "        -m <model>\n" );
	printf ( "          Model: can be one of norrish,\n" );

}

void getargs ( int argc, char **argv, info *user_data ) {

	int opt;

	user_data->model = malloc ( 8 * sizeof (char) );
	strcpy ( user_data->model, "norrish" );
	user_data->quiet = FALSE;

	while ( ( opt = getopt ( argc, argv, "hqf:m:" ) ) != -1 ) {
		switch (opt) {
			case 'h':
				free (user_data->model);
				print_usage ();
				exit (23);
				break;
			case 'q':
				user_data->quiet = TRUE;
				break;
			case 'f':
				user_data->filename = malloc (
					( strlen (optarg) + 1 ) * sizeof (char)
				);
				strcpy ( user_data->filename, optarg );
				break;
			case 'm':
				free(user_data->model);
				user_data->model = malloc (
					( strlen (optarg) + 1 ) * sizeof (char)
				);
				strcpy ( user_data->model, optarg );
				break;
		}

	}
}

