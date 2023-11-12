#ifndef FILEIO_H
#define FILEIO_H

typedef struct point_force {
	double location;
	double magnitude;
} point_force;

typedef struct dest_load {
	double start;
	double stop;
    // this is the pressure at start
	double pressure;
	int factor;
    // this is the pressure at stop
	double pressure2;
	double center;
	double weightf;
	double slope;
} dest_load;

typedef struct moment {
	double location;
	double magnitude;
} moment;

typedef struct reaction {
	double location;
	double magnitude;
	double moment;
} reaction;

void write_csv(double *x, double* M, double* S, double* T, double* Y, int num);
void get_nums(int array[]);
void read_txt(reaction R[], point_force P[], dest_load D[], moment M[], double *length);

#endif // FILEIO_H
