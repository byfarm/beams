#include <stdio.h>
#include <math.h>


float weight(float x1, float x2, float factor, float y1, float slope) {
    if (fabsf(slope) < 0.01 | fabsf(factor) <= 0.1) {
	float result = (x2 - x1) * y1;
	printf("weight c %f\n", result);
	return result;
    }
    printf("slope: %0.2f\n", slope);
    float term1 = slope / (factor + 1) * pow(x2, factor + 1);
    float term2 = slope / (factor + 1) * pow(x1, factor + 1);
    float result = term1 - term2;
    printf("weight %f\n", result);
    return result;
}


float position(float x1, float x2, float factor, float y1, float y2) {
    float fraction = (x2 - x1) / (factor + 2);
    printf("x1: %0.2f, x2: %.2f\n", x1, x2);
    printf("fraction: %.2f\n", fraction);
    float position;
    if (y1 < y2) {
	position = x2 - fraction;
    } else if (y1 > y2) {
	position = x1 + fraction;
    } else {
	position = (x1 + x2) / 2;
    }
    printf("position %f\n", position);
    return position;
}
