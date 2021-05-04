#include "definitions_and_headers.h"

void print_usage (void) {

	fprintf ( stderr, "Usage: FitWaterActivity [OPTIONS]\n" );
	fprintf ( stderr, "    Options:\n" );
	fprintf ( stderr, "        -h\n" );
	fprintf ( stderr, "          Show this help\n" );
	fprintf ( stderr, "        -q\n" );
	fprintf ( stderr, "          Quiet; hide verbose output\n" );
	fprintf ( stderr, "        -f <filename>\n" );
	fprintf ( stderr, "          File in which the activity data are stored\n" );
	fprintf ( stderr, "        -m <model>\n" );
	fprintf ( stderr, "          Model: can be one of norrish,\n" );

}

void getargs ( int argc, char **argv, info *user_data ) {

	int opt;

	if ( argc < 2 ) {
		fprintf ( stderr, "No arguments provided; for help, use -h\n" );
		fprintf ( stderr, "Aborting...\n" );
		exit (24);
	}

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

