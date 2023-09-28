#ifndef FILEIO_H
#define FILEIO_H

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

typedef struct reaction {
	float location;
	float magnitude;
	float *moment;
} reaction;

void write_csv(float *x, float* M, float* S, int num);
void get_nums(int array[]);
void read_txt(reaction R[], point_force P[], dest_load D[], moment M[], float *length);

#endif // FILEIO_H
