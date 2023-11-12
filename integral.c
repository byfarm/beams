#include <stdio.h>
#include "integral.h"


double d_area(double x1, double x2, double y1, double y2) {
	double area = (y1 + y2)/2 * (x2 - x1);
	// printf("y1: %f, y2: %f, x1: %f, x2: %f, area: %f\n", y1, y2, x1, x2, area);
	return area;
}

double tot_area(double *x, int points, double foo[]) {
	// printf("startx: %f, num iters: %i, foo: %f\n", *x, points, foo[points]);
	double sum_area = 0;
	for (int i = 0; i < points - 1; i++) {
		double *xp1 = x;
		xp1++;
		sum_area += d_area(*x, *xp1, foo[i], foo[i+1]);
		x++;
	}
	// printf("sum area: %f\n", sum_area);
	return sum_area;
}  


