#include <stdio.h>
#include <math.h>
#include "calc.h"

int main() {
	float start = 0;
	float stop = 10;
	float power = 1;
	float p1 = 0;
	float p2 = 5;
	float slope = -0.1;
	float weightf = area(start, stop, p1, p2);
	printf("%f\n", weightf);
	return 0;
}
