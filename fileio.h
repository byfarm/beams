#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 50

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
	    array[0] += 1;
	} else if (line[0] == 'P') {
	    array[1] += 1;
	} else if (line[0] == 'D') {
	    array[2] += 1;
	} else if (line[0] == 'M') {
	    array[3] += 1;
	} else {
	    printf("invalid input\n");
	}
    }
    fclose(file);
    printf("lengths_read\n");
}

void read_txt(point_force R[], point_force P[], dest_load D[], moment M[]) {

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

	char data[MAX_LINE_LENGTH - 2];

	for (int i = 2; line[i] != '\n'; i++) {
	    data[i - 2] = line[i];
	}
	if (line[0] == 'P') {

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
	    point_force *pf = (point_force*) malloc(sizeof(point_force));
	    pf->location = atof(location);
	    pf->magnitude = atof(magnitude);
	    P[pi] = *pf;
	    pi++;

	} else if (line[0] == 'R') {

	    char location[MAX_LINE_LENGTH];
	    char location2[MAX_LINE_LENGTH];
	    int i = 0;
	    while (data[i] != ';') {
		location[i] = data[i];
		i++;
	    }
	    i++;
	    int idx = i;
	    while (data[i] != '\n') {
		location2[i - idx] = data[i];
		i++;
	    }
	    point_force *pf = (point_force*) malloc(sizeof(point_force));
	    point_force *pf2 = (point_force*) malloc(sizeof(point_force));
	    pf->location = atof(location);
	    pf2->location = atof(location2);
	    R[ri] = *pf;
	    ri++;
	    R[ri] = *pf2;
	    ri++;

	} else if (line[0] == 'D') {

	    char start[MAX_LINE_LENGTH];
	    char stop[MAX_LINE_LENGTH];
	    char magnitude[MAX_LINE_LENGTH];
	    int i = 0;
	    while (data[i] != ':') {
		start[i] = data[i];
		i++;
	    }
	    i++;
	    int diff = i;
	    while (data[i] != ',') {
		stop[i - diff] = data[i];
		i++;
	    }
	    i++;
	    int idx = i;
	    while (data[i] != '\n') {
		magnitude[i - idx] = data[i];
		i++;
	    }
	    dest_load *dload = (dest_load*) malloc(sizeof(dest_load));
	    dload->start = atof(start);
	    dload->stop = atof(stop);
	    dload->pressure = atof(magnitude);
	    D[di] = *dload;
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
	    moment *mom = (moment*) malloc(sizeof(moment));
	    mom->location = atof(location);
	    mom->magnitude = atof(magnitude);
	    M[mi] = *mom;
	    mi++;

	} else {
	    printf("Invalid Input");
	}
    }
    fclose(file);
    printf("Data loaded\n");
}
