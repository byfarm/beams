#include <stdio.h>
#include <math.h>
#include "calc.h"

int main() {
	float start = 0;
	float stop = 10;
	float power = 1;
	float p1 = 4;
	float p2 = 2;
	float slope = (p2 - p1) / (stop - start);
	float weightf = weight(start, stop, power, p1, p2, slope);
	printf("%f\n", weightf);
	return 0;
}
