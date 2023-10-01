#include <stdio.h>
#include "integral.h"


float d_area(float x1, float x2, float y1, float y2) {
	float area = (y1 + y2)/2 * (x2 - x1);
	return area;
}

float tot_area(float *x, float points, float foo[]) {
	float sum_area;
	for (int i = 0; i < points - 1; i++) {
		float *xp1 = x;
		xp1++;
		sum_area += d_area(*x, *xp1, foo[i], foo[i+1]);
		x++;
	}
	return sum_area;
}  


