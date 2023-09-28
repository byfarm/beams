#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "fileio.h"
#include "calc.h"

float solve_shear_d(reaction support_reactions[], point_force pf_array[], dest_load d_load_array[], float x, int num_supp, int num_pf, int num_dloads) {
/* gives the shear at a particular point on the beam	 */
	// solves the shear diagram
	// init variables
	float dload = 0;
	float pf = 0;
	float supports = 0;

	// sum the support forces
	for (int i = 0; i < num_supp; i++) {
		if (x >= support_reactions[i].location) {
			supports += support_reactions[i].magnitude;
		}
	}

	// sum the load forces
	for (int i = 0; i < num_pf; i++) {
		if (x >= pf_array[i].location) {
			pf += pf_array[i].magnitude;
		}
	}

	// sum the destributed load forces
	for (int i = 0; i < num_dloads; i++) {
		if (x >= d_load_array[i].start && x <= d_load_array[i].stop) {
			float dweight = area(d_load_array[i].start, x, d_load_array[i].pressure, d_load_array[i].slope);
			// printf("sweight: %.2f\n", dweight);
			dload += (dweight);
		} else if (x > d_load_array[i].stop) {
			dload += d_load_array[i].weightf;
		}
	}

	// sum all
	float shear = dload + pf - supports;
	return -shear;
}


float solve_moment_d(reaction support_reactions[], point_force pf_array[], dest_load d_load_array[], moment M_array[], float x, int num_supp, int num_pf, int num_dloads, int num_moments) {
/* gives the moment at a particular point on the beam	 */
	// solves the moment diagram
	// init variables
	float dload = 0;
	float pf = 0;
	float M = 0;
	float supports = 0;

	// sum the moment of the support reactions
	for (int i = 0; i < num_supp; i++) {
		if (x >= support_reactions[i].location) {
			supports += support_reactions[i].magnitude * (x - support_reactions[i].location);
			supports += support_reactions[i].moment;
		}
	}

	// sum the moment of the point loads
	for (int i = 0; i < num_pf; i++) {
		if (x >= pf_array[i].location) {
			pf += pf_array[i].magnitude * (x - pf_array[i].location);
		}
	}

	// sum the moment of the destributed loads
	for (int i = 0; i < num_dloads; i++) {
		if (x >= d_load_array[i].start && x <= d_load_array[i].stop) {
			float n_w = area(d_load_array[i].start, x, d_load_array[i].pressure, d_load_array[i].slope) * (x - location(d_load_array[i].start, x, d_load_array[i].pressure, d_load_array[i].slope));
			// printf("position: %f\n", (position(d_load_array[i].start, x, d_load_array[i].factor, d_load_array[i].pressure, d_load_array[i].pressure2)));
			// printf("dweight: %f\n", weight(d_load_array[i].start, x, d_load_array[i].factor, d_load_array[i].pressure, d_load_array[i].pressure2, d_load_array[i].slope));
			// printf("x: %.2f\n", x);
			// printf("ndload: %.2f\n", n_w);
			dload += n_w;
		} else if (x > d_load_array[i].stop) {
			float n_w = d_load_array[i].weightf * (x - d_load_array[i].center);
			dload += n_w;
		}
	}

	// sum the moments
	for (int i = 0; i < num_moments; i++) {
		if (x >= M_array[i].location) {
			M += M_array[i].magnitude;
		}
	}

	// sum all
	float moment = dload + pf + M - supports;
	return -moment;
}

void solve_cantilever(reaction fixed_end, float length, point_force force_array[], int num_forces, dest_load d_loads[], int num_dloads, moment moments[], int num_moments) {
	// sum the point forces
	float Fnetm = 0;
	float Fnet = 0;

	// must do this because when solving for reactions need to cancel out 1 unknown
	float loc_offset = fixed_end.location;

	for (int i = 0; i < num_forces; i++) {
		Fnetm += (force_array[i].location - loc_offset) * force_array[i].magnitude;
		Fnet += force_array[i].magnitude;
	}

	// find the sum of the dloads
	for (int i = 0; i < num_dloads; i++) {
		Fnetm += d_loads[i].weightf * (d_loads[i].center - loc_offset);
		Fnet += d_loads[i].weightf;
	}

	fixed_end.moment = Fnetm;
	fixed_end.magnitude = Fnet;
}

void solve_reactions(reaction support_reactions[],int num_supports, float length, point_force force_array[], int num_forces, dest_load d_loads[], int num_dloads, moment moments[], int num_moments) {
/* solves the reactions using sum of moments then sum of forces */
	// solves for the reactions
	// sum the point forces
	float Fnetm = 0;
	float Fnet = 0;

	// must do this because when solving for reactions need to cancel out 1 unknown
	float loc_offset = support_reactions[0].location;

	for (int i = 0; i < num_forces; i++) {
		Fnetm += (force_array[i].location - loc_offset) * force_array[i].magnitude;
		Fnet += force_array[i].magnitude;
	}

	// find the sum of the dloads
	for (int i = 0; i < num_dloads; i++) {
		Fnetm += d_loads[i].weightf * (d_loads[i].center - loc_offset);
		Fnet += d_loads[i].weightf;
	}

	// solve for the reactions using sum of moments then sum forces in y
	float reactionB = (Fnetm) / (support_reactions[1].location - support_reactions[0].location);
	for (int i = 0; i < num_moments; i++) {
		reactionB -= moments[i].magnitude / (support_reactions[1].location - support_reactions[0].location);
	}
	float reactionA = Fnet - reactionB;

	// put results into array datastructure
	support_reactions[0].magnitude = reactionA;
	support_reactions[1].magnitude = reactionB;
}

float* linspace(float start, float stop, int len) {
	// creates a linearly spaced array of floats
	float *array = (float*)malloc(len * sizeof(float));
	float step = (stop - start) / (len - 1);
	for (int i = 0; i < len; ++i) {
		array[i] = (i * step) + start;
	}
	return array;
}

int main() {

	float length;
	int indexes[4] = {0};
	get_nums(indexes);
	int num_supports = indexes[0]; 
	// printf("num supports %i/n", num_supports);
	int num_point_forces = indexes[1];
	int num_dest_loads = indexes[2];
	int num_moments = indexes[3];
	reaction support_reactions[num_supports];
	point_force pf_array[num_point_forces];
	dest_load d_load_array[num_dest_loads];
	moment M_array[num_moments];
	read_txt(support_reactions, pf_array, d_load_array, M_array, &length);
	if (num_supports < 2) {
			// solve the reaction
			solve_cantilever(support_reactions[0], length, pf_array, num_point_forces, d_load_array, num_dest_loads, M_array, num_moments);
			printf("\nReaction Force: %0.2f lbs\nReaction Moment: %0.2f lb-ft\n", support_reactions[0].magnitude, support_reactions[0].moment);
	} else {
		// get reactions at 2 supports
		solve_reactions(support_reactions, num_supports, length, pf_array, num_point_forces, d_load_array, num_dest_loads, M_array, num_moments);
		printf("\nReaction A: %0.2f lbs\nReaction B: %0.2f lbs\n", support_reactions[0].magnitude, support_reactions[1].magnitude);
	}
	// printf("len %f\n", length);
	// all units are in lbs/ft


	/* // length of beam
	float length = 14;
	// location of the supports
	float sup_loc[] = {3, 10};
	// // // point forces
	float force[] = {};
	float location[] = {};
	// // // destributed loads
	float pressure[] = {};
	float starts[] = {};
	float stops[] = {};
	// // // moments
	float M[] = {10};
	float position[] = {0};
	// // 
	// // // solve the reactions
	int num_supports = sizeof(sup_loc)/ sizeof(sup_loc[0]);
	point_force support_reactions[num_supports];
	for (int i = 0; i < num_supports; i++) {
		support_reactions[i].location = sup_loc[i];
		if (sup_loc[i] < 0 || sup_loc[i] > length) {
			printf("force is off the beam");
			return 1;
		}
	}
	// //
	// // // put point forces into structure
	int num_point_forces = sizeof(force)/ sizeof(force[0]);
	point_force pf_array[num_point_forces];
	for (int i = 0; i < num_point_forces; i++) {
		pf_array[i].location = location[i];
		pf_array[i].magnitude = force[i];
		if (location[i] < 0 || location[i] > length) {
			printf("force is off the beam");
			return 1;
		}
	}
	// //
	// // // put destributed loads into structure
	int num_dest_loads = sizeof(pressure)/ sizeof(pressure[0]);
	dest_load d_load_array[num_dest_loads];
	for (int i = 0; i < num_dest_loads; i++) {
		d_load_array[i].pressure = pressure[i];
		d_load_array[i].start = starts[i];
		d_load_array[i].stop = stops[i];
		if (starts[i] < 0 || stops[i] > length || starts[i] > stops[i]) {
			printf("destributed load is off the beam");
			return 1;
		}
	}
	//
	// // put moments into structure
	int num_moments = sizeof(M)/ sizeof(M[0]);
	moment M_array[num_moments];
	for (int i = 0; i < num_moments; i++) {
		M_array[i].location = position[i];
		M_array[i].magnitude = M[i];
		if (location[i] < 0 || location[i] > length) {
			printf("force is off the beam");
			return 1;
		}
	} */
	

	// make plot points
	int points = 100000;
	float *x = linspace(0, length, points);
	float all_shear[points];
	float all_M[points];
	
	// plug into equations
	for (int i = 0; i < points; i++) {
		all_shear[i] = solve_shear_d(support_reactions, pf_array, d_load_array, *x, num_supports, num_point_forces, num_dest_loads);
		all_M[i] = solve_moment_d(support_reactions, pf_array, d_load_array, M_array, *x, num_supports, num_point_forces, num_dest_loads, num_moments);
		// printf("%.2f %.2f %.2f\n", *x, all_shear[i], all_M[i]);
		x++;
	}
	// have to reset x pointer back to begining
	for (int i = 0; i < points; i++) {
		x--;
	}
	write_csv(x, all_M, all_shear, points);

	return 0;
}
