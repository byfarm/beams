#include <stdio.h>
#include <math.h>
#include "calc.h"

int main() {
	float start = 0;
	float stop = 10;
	float p1 = 1;
	float slope = -0.1;
	float weightf = location(start, stop, p1, slope);
	printf("%f\n", weightf);
	return 0;
}
