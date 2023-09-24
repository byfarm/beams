#include <stdio.h>
#include <math.h>
#include "calc.h"

int main() {
	float start = 3;
	float stop = 8;
	float power = 2;
	float p1 = 2;
	float p2 = 3;
	float weightf = weight(start, stop, power, p1, p2);
	printf("%f\n", weightf);
	return 0;
}
