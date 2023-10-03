#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"
#include "fileio.h"

#define MAX_LINE_LENGTH 64

void write_csv(float *x, float* M, float* S, int num) {
    // write data to the csv file to be graphed by the python script
    FILE *file;
    file = fopen("data.csv", "w");
    if (file == NULL) {
	    printf("Error opening file\n");
    }
    fprintf(file, "%s,%s,%s", "x", "S", "M");
    
    // write the x, S, and M line by line into the file
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
    // gets the number of each type of force to preallocate an array for each
    FILE *file;
    char line[MAX_LINE_LENGTH];

    file = fopen("inputs.txt", "r");
    if (file == NULL) {
        printf("Error opening input file\n");
    }

    // read through the file line by line
    while (fgets(line, MAX_LINE_LENGTH, file)) {
	// first get number of supports, then everything else
	if (line[0] =='R') {
	    array[0]++;
	} else if (line[0] == 'P') {
	    array[1] += 1;
	} else if (line[0] == 'D') {
	    array[2] += 1;
	} else if (line[0] == 'M') {
	    array[3] += 1;
	} else if (line[0] == 'L') {
	    // skip over length def
	} else {
	    printf("invalid input\n");
	}
    }
    fclose(file);
    // printf("Lengths read\n");
}

void read_txt(reaction R[], point_force P[], dest_load D[], moment M[], float *length) {

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

    // read file line by line, printing out each one
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        printf("%s", line);

	char *data;
	// take out the first two characters of the data
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

	    // char *token;
	    reaction reac; // = (point_force*) malloc(sizeof(point_force));
	    // token = strtok(data, ",");
	    reac.location = atof(data);
	    reac.moment = 0.0;
	    // printf("reaction loc %f\n", pf->location);
	    // printf("reaction2 loc %f\n", pf2->location);
	    R[ri] = reac;
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
	    dload.weightf = area(dload.start, dload.stop, dload.pressure, dload.slope);
	    dload.center = location(dload.start, dload.stop, dload.pressure, dload.slope);
	    // printf("center: %f\n", dload.center);
	    // printf("weight: %f\n", dload.weightf);

	    D[di] = dload;
	    di++;

	} else if (line[0] == 'M') {
	    moment mom; // = (moment*) malloc(sizeof(moment));
	    char *token;
	    token = strtok(data, ",");
	    mom.location = atof(token);
	    while (token != NULL) {
		mom.magnitude = atof(token);
		token = strtok(NULL, ",");
	    }

	    // printf("pf mag %f\n", pf->magnitude);
	    // printf("pf loc %f\n", pf->location);
	    M[mi] = mom;
	    mi++;
	    // free(mom);

	} else if (line[0] == 'L') {

	    *length = atof(data);
	    // printf("len %f\n", *length);

	} else {
	    printf("Invalid Input\n");
	}
    }
    // printf("closing file\n");
    fclose(file);
    // printf("Data loaded\n");
};
