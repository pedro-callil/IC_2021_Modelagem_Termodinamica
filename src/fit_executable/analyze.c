#include "definitions_and_headers.h"

void analyze_all_models ( System *data, info *user_data ) {

	free (user_data->model);
	user_data->model = malloc ( strlen ("norrish") + 1 );
	strcpy ( user_data->model, "norrish" );
	fit_to_model ( data, user_data );
	fprintf ( stdout, "Final cost for norrish's model:\t\t%f\n",
			user_data->cost );

	free (user_data->model);
	user_data->model = malloc ( strlen ("virial") + 1 );
	strcpy ( user_data->model, "virial" );
	fit_to_model ( data, user_data );
	fprintf ( stdout, "Final cost for virial model:   \t\t%f\n",
			user_data->cost );

	free (user_data->model);
	user_data->model = malloc ( strlen ("raoult") + 1 );
	strcpy ( user_data->model, "raoult" );
	check_model ( data, user_data );
	fprintf ( stdout, "Final cost for raoult's model: \t\t%f\n",
			user_data->cost );

	free (user_data->model);
	user_data->model = malloc ( strlen ("caurie") + 1 );
	strcpy ( user_data->model, "caurie" );
	check_model ( data, user_data );
	fprintf ( stdout, "Final cost for caurie's model: \t\t%f\n",
			user_data->cost );

}
