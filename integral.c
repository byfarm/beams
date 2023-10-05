#include <stdio.h>
#include "integral.h"


float d_area(float x1, float x2, float y1, float y2) {
	float area = (y1 + y2)/2 * (x2 - x1);
	// printf("y1: %f, y2: %f, x1: %f, x2: %f, area: %f\n", y1, y2, x1, x2, area);
	return area;
}

float tot_area(float *x, int points, float foo[]) {
	// printf("startx: %f, num iters: %i, foo: %f\n", *x, points, foo[points]);
	float sum_area = 0;
	for (int i = 0; i < points - 1; i++) {
		float *xp1 = x;
		xp1++;
		sum_area += d_area(*x, *xp1, foo[i], foo[i+1]);
		x++;
	}
	// printf("sum area: %f\n", sum_area);
	return sum_area;
}  


