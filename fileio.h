#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"

#define MAX_LINE_LENGTH 64

typedef struct point_force {
	float location;
	float magnitude;
} point_force;

typedef struct dest_load {
	float start;
	float stop;
    // this is the pressure at start
	float pressure;
	int factor;
    // this is the pressure at stop
	float pressure2;
	float center;
	float weightf;
	float slope;
} dest_load;

typedef struct moment {
	float location;
	float magnitude;
} moment;


void write_csv(float *x, float* M, float* S, int num) {
	// write data to the csv file to be graphed by the python script
	FILE *file;
	file = fopen("data.csv", "w");
	if (file == NULL) {
		printf("Error opening file\n");
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

void get_nums(int array[]) {
    FILE *file;
    char line[MAX_LINE_LENGTH];

    file = fopen("inputs.txt", "r");
    if (file == NULL) {
        printf("Error opening input file\n");
    }

    while (fgets(line, MAX_LINE_LENGTH, file)) {
	if (line[0] == 'R') {
	    char *token;
	    token = strtok(line, ";");
	    while (token != NULL) {
		array[0] += 1;
		token = strtok(NULL, ";");
	    }
	    array[0]--;
	} else if (line[0] == 'P') {
	    array[1] += 1;
	} else if (line[0] == 'D') {
	    array[2] += 1;
	} else if (line[0] == 'M') {
	    array[3] += 1;
	} else if (line[0] == 'L') {
	} else {
	    printf("invalid input\n");
	}
    }
    fclose(file);
    printf("Lengths read\n");
}

void read_txt(point_force R[], point_force P[], dest_load D[], moment M[], float *length) {

    FILE *file;
    char line[MAX_LINE_LENGTH];
    int ri = 0;
    int pi = 0;
    int di = 0;
    int mi = 0;

    file = fopen("inputs.txt", "r");
    if (file == NULL) {
        printf("Error opening input file\n");
    }

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        printf("%s", line);

	char *data;
	data = line + 2;

	if (line[0] == 'P') {

	    point_force pf; // = (point_force*) malloc(sizeof(point_force));
	    char *token;
	    token = strtok(data, ",");
	    pf.location = atof(token);
	    while (token != NULL) {
		pf.magnitude = atof(token);
		token = strtok(NULL, ",");
	    }

	    // printf("pf mag %f\n", pf->magnitude);
	    // printf("pf loc %f\n", pf->location);
	    P[pi] = pf;
	    pi++;
	    // free(pf);

	} else if (line[0] == 'R') {

	    char *token;
	    point_force pf; // = (point_force*) malloc(sizeof(point_force));
	    point_force pf2;//  = (point_force*) malloc(sizeof(point_force));
	    token = strtok(data, ";");
	    pf.location = atof(token);
	    while (token != NULL) {
		pf2.location = atof(token);
		token = strtok(NULL, ";");
	    }
	    // printf("reaction loc %f\n", pf->location);
	    // printf("reaction2 loc %f\n", pf2->location);
	    R[ri] = pf;
	    ri++;
	    R[ri] = pf2;
	    ri++;
	    // free(pf), free(pf2);

	} else if (line[0] == 'D') {

	    char *token;
	    token = strtok(data, ",");
	    char *len_data = token;
	    token = strtok(NULL, ",");
	    char *pressure_data = token;
	    token = strtok(NULL, ",");
	    int factor = atoi(token);
	    // printf("d data: %s %s %i\n", len_data, pressure_data, factor);
	    dest_load dload; // = (dest_load*) malloc(sizeof(dest_load));

	    char *ststop;
	    ststop = strtok(len_data, ":");
	    dload.start = atof(ststop);
	    ststop = strtok(NULL, ":");
	    dload.stop = atof(ststop);

	    char *pd;
	    pd = strtok(pressure_data, ":");
	    dload.pressure = atof(pd);
	    pd = strtok(NULL, ":");
	    dload.pressure2 = atof(pd);

	    dload.factor = factor;
	    dload.slope = (dload.pressure2 - dload.pressure) / (dload.stop - dload.start);
	    dload.weightf = weight(dload.start, dload.stop, dload.factor, dload.pressure, dload.pressure2, dload.slope);
	    dload.center = position(dload.start, dload.stop, dload.factor, dload.pressure, dload.pressure2);
	    // printf("center: %f\n", dload.center);
	    // printf("weight: %f\n", dload.weightf);

	    D[di] = dload;
	    di++;

	} else if (line[0] == 'M') {

	    char location[MAX_LINE_LENGTH];
	    char magnitude[MAX_LINE_LENGTH];
	    int i = 0;
	    while (data[i] != ',') {
		location[i] = data[i];
		i++;
	    }
	    i++;
	    int idx = i;
	    while (data[i] != '\n') {
		magnitude[i - idx] = data[i];
		i++;
	    }
	    moment mom; // = (moment*) malloc(sizeof(moment));
	    mom.location = atof(location);
	    mom.magnitude = atof(magnitude);
	    M[mi] = mom;
	    // printf("moment mag %f\n", mom->magnitude);
	    // printf("moment loc %f\n", mom->location);
	    mi++;
	    // free(mom);

	} else if (line[0] == 'L') {

	    *length = atof(data);
	    // printf("len %f\n", *length);

	} else {
	    printf("Invalid Input\n");
	}
    }
    fclose(file);
    printf("Data loaded\n");
};
