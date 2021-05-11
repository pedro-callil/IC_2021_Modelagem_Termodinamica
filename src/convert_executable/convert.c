#include "definitions_and_headers.h"

double arden_buck ( double T ) {
	return ( A_A * exp ( ( B_A - T / C_A ) * ( T / ( D_A + T ) ) ) );
}

Data convert ( Metadata *system_description, Data *system,
		info *user_data ) {

	Data new_system;
	double **x, **x_var;
	double *aw, *y_var;
	int lines, comps, i, j;
	double tmp_xtot_for_molality, tmp_xw_for_phi;
	double tmp_mw_for_mass_fraction, tmp_xw_for_mass_fraction,
		tmp_xtot_for_mass_fraction;
	double pure_pressure;

	lines = system_description->dataset_size;
	comps = system_description->n_of_comps;

	x_var = system->x;
	y_var = system->aw;

	x = malloc ( lines * sizeof (double *) );
	aw = malloc ( lines * sizeof (double) );
	for ( i = 0; i < lines; i ++ ) {
		x[i] = malloc ( comps * sizeof (double) );
	}

	/*
	* * In this part of the file we deal with the
	* * variables associated to concentration, with
	* * the conversion of the properties in molar
	* * molar fractions.
	*/

	if ( strcmp ( user_data->x_property, "molality" ) == TRUE ) {
		for ( i = 0; i < lines; i++ ) {
			tmp_xtot_for_molality = MOLALITY_TO_FRACTION;
			for ( j = 0; j < comps; j++ ) {
				tmp_xtot_for_molality += x_var[i][j];
			}
			for ( j = 0; j < comps; j++ ) {
				x[i][j] = x_var[i][j] / tmp_xtot_for_molality;
			}
		}
	}      /*
		* Here we convert molality data in molar fraction data;
		*/

	if ( strcmp ( user_data->x_property, "mass_fraction" ) == TRUE ) {
		for ( i = 0; i < lines; i++ ) {
			tmp_mw_for_mass_fraction = 1;
			tmp_xtot_for_mass_fraction = 0;
			for ( j = 0; j < comps; j++ ) {
				tmp_mw_for_mass_fraction -= x_var[i][j];
				x[i][j] = x_var[i][j] /
					user_data->molar_masses[j];
				tmp_xtot_for_mass_fraction += x[i][j];
			}
			tmp_xw_for_mass_fraction =
				tmp_mw_for_mass_fraction / MASS_TO_FRACTION;
			tmp_xtot_for_mass_fraction += tmp_xw_for_mass_fraction;
			for ( j = 0; j < comps; j++ ) {
				x[i][j] = x[i][j] / tmp_xtot_for_mass_fraction;
			}
		}
	}      /*
		* Here we convert mass fraction data in molar fraction data.
		*/

	if ( strcmp ( user_data->x_property, "mass_concentration" ) == TRUE ) {
		for ( i = 0; i < lines; i++ ) {
			tmp_mw_for_mass_fraction = 1000;
			tmp_xtot_for_mass_fraction = 0;
			for ( j = 0; j < comps; j++ ) {
				x[i][j] = x_var[i][j] /
					user_data->molar_masses[j];
				tmp_xtot_for_mass_fraction += x[i][j];
			}
			tmp_xw_for_mass_fraction =
				tmp_mw_for_mass_fraction / MASS_TO_FRACTION;
			tmp_xtot_for_mass_fraction += tmp_xw_for_mass_fraction;
			for ( j = 0; j < comps; j++ ) {
				x[i][j] = x[i][j] / tmp_xtot_for_mass_fraction;
			}
		}
	}      /*
		* Here we convert mass concentration data in molar fraction data.
		*/

	if ( strcmp ( user_data->x_property, "molar_concentration" ) == TRUE ) {
		for ( i = 0; i < lines; i++ ) {
			tmp_mw_for_mass_fraction = 1000;
			tmp_xtot_for_mass_fraction = 0;
			for ( j = 0; j < comps; j++ ) {
				tmp_xtot_for_mass_fraction += x_var[i][j];
			}
			tmp_xw_for_mass_fraction =
				tmp_mw_for_mass_fraction / MASS_TO_FRACTION;
			tmp_xtot_for_mass_fraction += tmp_xw_for_mass_fraction;
			for ( j = 0; j < comps; j++ ) {
				x[i][j] = x_var[i][j] / tmp_xtot_for_mass_fraction;
			}
		}
	}      /*
		* Here we convert molar concentration data in molar fraction data.
		*/

	/*
	* * In this other half, we proceed to convert data from boiling
	* * point elevation, freeze point depression, vapour pressure and
	* * osmotic coefficient in water activity data.
	*/
	if ( strcmp ( user_data->y_property, "phi" ) == TRUE ||
		strcmp ( user_data->y_property, "osmotic_coefficient" ) == TRUE ) {
		for ( i = 0; i < lines; i++ ) {
			tmp_xw_for_phi = 1;
			for ( j = 0; j < comps; j++ ) {
				tmp_xw_for_phi -= x_var[i][j];
			}
			aw[i] = pow ( tmp_xw_for_phi, y_var[i] );
		}
	}      /*
		* Here we convert the osmotic coefficient phi in water activity data;
		* N.b.: the x must be already molar fraction data. So this comes last.
		*/

	if ( strcmp ( user_data->y_property, "vapour_pressure" ) == TRUE ||
		strcmp ( user_data->y_property, "vapor_pressure" ) == TRUE ) {
		pure_pressure = arden_buck ( user_data->temperature );
		for ( i = 0; i < lines; i++ ) {
			aw[i] = y_var[i] / pure_pressure;
		}
	}      /*
		* Here we convert vapour pressure data in water activity (via
		* ERH); the vapour pressure of pure water is approximated with
		* empirical relations, especifically the Arden Buck equation.
		*/

	new_system.x = x;
	new_system.aw = aw;

	return new_system;
}
