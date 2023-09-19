#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct point_force {
	float location;
	float magnitude;
} point_force;

typedef struct dest_load {
	float start;
	float stop;
	float pressure;
} dest_load;

typedef struct moment {
	float location;
	float magnitude;
} moment;

float solve_shear_d(point_force support_reactions[], point_force pf_array[], dest_load d_load_array[], float x, int num_supp, int num_pf, int num_dloads) {
	// solves the shear diagram
	// init variables
	float dload = 0;
	float pf = 0;

	// sum the support forces
	for (int i = 0; i < num_supp; i++) {
		if (x >= support_reactions[i].location) {
			pf -= support_reactions[i].magnitude;
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
			dload += d_load_array[i].pressure * (x - d_load_array[i].start);
		} else if (x >= d_load_array[i].start && x > d_load_array[i].stop) {
			dload += d_load_array[i].pressure * (d_load_array[i].stop - d_load_array[i].start);
		}
	}

	// sum all
	float shear = dload + pf;
	return shear;
}


float solve_moment_d(point_force support_reactions[], point_force pf_array[], dest_load d_load_array[], moment M_array[], float x, int num_supp, int num_pf, int num_dloads, int num_moments) {
	// solves the moment diagram
	// init variables
	float dload = 0;
	float pf = 0;
	float M = 0;

	// sum the moment of the support reactions
	for (int i = 0; i < num_supp; i++) {
		if (x >= support_reactions[i].location) {
			float j = support_reactions[i].magnitude * (x - support_reactions[i].location);
			pf -= j;
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
			float j = d_load_array[i].pressure * (x - d_load_array[i].start) * ((x - d_load_array[i].start) / 2); 
			dload += j;
		} else if (x >= d_load_array[i].start && x > d_load_array[i].stop) {
			float k = d_load_array[i].pressure * (d_load_array[i].stop - d_load_array[i].start) * (x - ((d_load_array[i].stop + d_load_array[i].start)/2));
			dload += k;
		}
	}

	// sum the moments
	for (int i = 0; i < num_moments; i++) {
		if (x >= M_array[i].location) {
			M -= M_array[i].magnitude;
		}
	}

	// sum all
	float moment = dload + pf + M;
	return moment;
}


void solve_reactions(point_force support_reactions[],int num_supports, float length, point_force force_array[], int num_forces, dest_load d_loads[], int num_dloads, moment moments[], int num_moments) {
	// solves for the reactions
	// sum the point forces
	float Fnetm = 0;
	float Fnet = 0;
	for (int i = 0; i < num_forces; i++) {
		Fnetm += force_array[i].location * force_array[i].magnitude;
		Fnet += force_array[i].magnitude;
	}

	// find the sum of the dloads
	for (int i = 0; i < num_dloads; i++) {
		Fnetm += (d_loads[i].stop - d_loads[i].start) * d_loads[i].pressure * (d_loads[i].start + d_loads[i].stop) / 2;
		Fnet += (d_loads[i].stop - d_loads[i].start) * d_loads[i].pressure;
	}

	// solve for the reactions
	float reactionB = Fnetm / length;
	for (int i = 0; i < num_moments; i++) {
		reactionB += moments[i].magnitude / length;
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

void write_csv(float *x, float* M, float* S, int num) {
	FILE *file;
	file = fopen("data.csv", "w");
	if (file == NULL) {
		printf("Error opening file/n");
	}
	fprintf(file, "%i,%i,%i", 1, 2, 3);
	for (int i = 0; i < num; i++) {
		fprintf(file, "%0.2f,%0.2f,%0.2f\n", *x, *S, *M);
		if (ferror(file)) {printf("error printing to file");}
		x++;
		M++;
		S++;
	}
	fclose(file);
}

int main() {
	// all units are in lbs/ft

	// length of beam
	float length = 10;
	// number of supports
	float sup_loc[] = {0, length};
	// point forces
	float force[] = {};
	float location[] = {};
	// destributed loads
	float pressure[] = {};
	float starts[] = {};
	float stops[] = {};
	// moments
	float M[] = { 10 };
	float position[] = { 5 };
	
	// solve the reactions
	int num_supports = sizeof(sup_loc)/ sizeof(sup_loc[0]);
	point_force support_reactions[num_supports];
	for (int i = 0; i < num_supports; i++) {
		support_reactions[i].location = sup_loc[i];
		if (sup_loc[i] < 0 || sup_loc[i] > length) {
			printf("force is off the beam");
			return 1;
		}
	}

	// put point forces into structure
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

	// put destributed loads into structure
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

	// put moments into structure
	int num_moments = sizeof(M)/ sizeof(M[0]);
	moment M_array[num_moments];
	for (int i = 0; i < num_moments; i++) {
		M_array[i].location = position[i];
		M_array[i].magnitude = M[i];
		if (location[i] < 0 || location[i] > length) {
			printf("force is off the beam");
			return 1;
		}
	}

	// get reactions at 2 supports
	solve_reactions(support_reactions, num_supports, length, pf_array, num_point_forces, d_load_array, num_dest_loads, M_array, num_moments);
	printf("Reaction A: %0.2f lbs\nReaction B: %0.2f lbs\n", support_reactions[0].magnitude, support_reactions[1].magnitude);

	// make plot points
	int points = 10000;
	float *x = linspace(0, length, points);
	float all_shear[points];
	float all_M[points];
	
	// plug into equations
	for (int i = 0; i < points; i++) {
		all_shear[i] = solve_shear_d(support_reactions, pf_array, d_load_array, *x, num_supports, num_point_forces, num_dest_loads);
		all_M[i] = solve_moment_d(support_reactions, pf_array, d_load_array, M_array, *x, num_supports, num_point_forces, num_dest_loads, num_moments);
		x++;
	}
	for (int i = 0; i < points; i++) {
		x--;
	}
	write_csv(x, all_M, all_shear, points);

	return 0;
}

