# include "definitions_and_headers.h"

/*
 * This function reads data from a file and stores it in a struct of type Data.
 * It also stores the number of data points, the number of components and their
 * names in another struct, of type Metadata. Its arguments are the name of the
 * .csv file in which the data are stored, and pointers to the structs.
 */

void initialize ( char *filename, Metadata *system_description, Data *system ) {

	int lines, columns, line_is_empty;
	char tmpchar;
	char **composition;
	double **x_values;
	double *y_values;
	FILE *file;

	file = fopen ( *filename, "r" );
	lines = -1;
	columns = 0;
	line_is_empty = TRUE;
	do {
		tmpchar = fgetc ( file );
		if ( (tmpchar == '\n') && (line_is_empty == FALSE) ) {
			lines ++;
			line_is_empty = TRUE;
		} else if ( tmpchar == ',' ) {
			columns ++;
			line_is_empty = FALSE;
		}
	} while ( tmpchar != EOF );
	fclose ( file );
	columns = columns / lines;
		/*
		* Here we get the number of components and
		* data points in the file (lines and columns)
		*/

	system_description->dataset_size = lines;
	system_description->n_of_comps = columns;

	composition = malloc ( columns * sizeof(char *) );
	system_description->components = composition;

	x_values = malloc ( lines * sizeof(double *) );
	y_values = malloc ( lines * sizeof(double) );
	for ( i = 0; i < lines; i++ ) {
		x_values[i] = malloc ( columns * sizeof (double) );
	}
	system->x = x_values;
	system->aw = y_values;
		/*
		* And now our structures are allocated
		*/

}

