#include "definitions_and_headers.h"

/* print accepted arguments and options */
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
	fprintf ( stderr, "          Model: can be one of norrish, virial, \n" );
	fprintf ( stderr, "          caurie, raoult or all, option which \n" );
	fprintf ( stderr, "          compares all other models. \n" );

}

/* read arguments and options from user */
void getargs ( int argc, char **argv, info *user_data ) {

	int opt, gave_file;

	gave_file = FALSE;

	if ( argc < 2 ) {
		fprintf ( stderr, "No arguments provided; for help, use -h\n" );
		fprintf ( stderr, "Aborting...\n" );
		exit (24);
	}

	user_data->model = malloc ( 8 * sizeof (char) );
	strcpy ( user_data->model, "raoult" );
	user_data->quiet = FALSE;
	user_data->cost = 0;
	user_data->is_all = FALSE;

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
				gave_file = TRUE;
				if ( access( optarg, F_OK|R_OK ) == TRUE ) {
					user_data->filename = malloc (
						( strlen (optarg) + 1 ) *
						sizeof (char)
					);
					strcpy ( user_data->filename, optarg );
				} else {
					fprintf ( stderr,
					"File not found or wrong permissions. " );
					fprintf ( stderr, "Aborting...\n" );
					free(user_data->model);
					exit (34);
				}
				break;
			case 'm':
				free(user_data->model);
				user_data->model = malloc (
					( strlen (optarg) + 1 ) * sizeof (char)
				);
				strcpy ( user_data->model, optarg );
				if ( strcmp ( user_data->model, "all" ) == TRUE ) {
					user_data->is_all = TRUE;
					user_data->quiet = TRUE;
				}
				break;
		}

	}

	if ( gave_file == FALSE ) {
		fprintf ( stderr, "No filename given, aborting...\n" );
		free (user_data->model);
		exit (24);
	}
}

