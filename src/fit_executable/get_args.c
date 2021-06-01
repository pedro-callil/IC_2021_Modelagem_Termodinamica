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
	fprintf ( stderr, "        -F <filename to store predicted values>\n" );
	fprintf ( stderr, "          File to store the calculated values.\n" );
	fprintf ( stderr, "        -Z <1st filename> <2nd filename>\n" );
	fprintf ( stderr, "          If the model chosen is \"zdanovskii\",\n" );
	fprintf ( stderr, "          these two files must store the isotherms\n" );
	fprintf ( stderr, "          of the two components of the ternary mixture\n" );
	fprintf ( stderr, "          in a binary solution.\n" );
	fprintf ( stderr, "        -m <model>\n" );
	fprintf ( stderr, "          Model: can be one of norrish, virial, \n" );
	fprintf ( stderr, "          UNIQUAC, caurie, raoult, zdanovskii \n" );
	fprintf ( stderr, "          or all, which compares all other models. \n" );
	fprintf ( stderr, "        -O\n" );
	fprintf ( stderr, "          Fit models that need only one one file,\n" );
	fprintf ( stderr, "          currently all but \"zdanovskii\". Useful\n" );
	fprintf ( stderr, "          for combination with option \"-m all\".\n" );

}

/* read arguments and options from user */
void getargs ( int argc, char **argv, info *user_data ) {

	int opt, gave_file, index, count;

	gave_file = FALSE;
	user_data->gave_filenames = FALSE;

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
	user_data->not_zdan = FALSE;
	user_data->files_zdan = NULL;
	user_data->save_new_results = FALSE;
	user_data->filename_new_results = NULL;

	while ( ( opt = getopt ( argc, argv, "hqf:F:m:Z:O" ) ) != -1 ) {
		switch (opt) {
			case 'h':
				free (user_data->model);
				print_usage ();
				exit (23);
				break;
			case 'q':
				user_data->quiet = TRUE;
				break;
			case 'O':
				user_data->not_zdan = TRUE;
				break;
			case 'Z':
				user_data->files_zdan =
					malloc ( 2 * sizeof (char *) );
				index = optind - 1;
				count = 0;
				while ( index < argc ) {
					if ( argv[index][0] != '-' ) {
						user_data->files_zdan[count] =
							malloc ( strlen (argv[index])
									+ 1 );
						strcpy ( user_data->files_zdan[count],
								argv[index] );
						count++;
					} else break;
					index ++;
				}
				if ( count >= 2 ) {
					user_data->gave_filenames = TRUE;
				}
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
			case 'F':
				user_data->save_new_results = TRUE;
				user_data->filename_new_results =
					malloc ( ( strlen (optarg) + 1 ) *
					sizeof (char) );
				strcpy ( user_data->filename_new_results,
						optarg );
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

	if ( user_data->gave_filenames == FALSE &&
			strcmp ( user_data->model, "zdanovskii" ) == TRUE ) {
		fprintf ( stderr, "No isotherms given for Zdanovskii Relation." );
		fprintf ( stderr, " Aborting.\n" );
		free (user_data->model);
		if ( user_data->filename != NULL ) {
			free (user_data->filename);
		}
		if ( user_data->files_zdan != NULL ) {
			if ( user_data->files_zdan[0] != NULL ) {
				free (user_data->files_zdan[0]);
			}
			free (user_data->files_zdan);
		}
		exit (24);
	}
}

