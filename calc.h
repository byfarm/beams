#include <stdio.h>
#include <math.h>


float weight(float x1, float x2, float factor, float y1, float y2, float slope) {
    if (fabsf(slope) < 0.01 | fabsf(factor) <= 0.01) {
	float result = (x2 - x1) * y1;
	// printf("weight c %f\n", result);
	return result;
    }
    // printf("slope: %0.2f\n", slope);
    float term1, term2, term1c, term2c, result;
    term1 = slope / (factor + 1) * pow(x2, factor + 1);
    term2 = slope / (factor + 1) * pow(x1, factor + 1);
    // if (slope > 0) {
    term1c = y1 * x2;
    term2c = y1 * x1;
    // } else {
	// slope = -slope;
	// term1c = y2 * x2;
	// term2c = y2 * x1;
	
	// slope = -slope;
	// printf("slope: %0.2f\n", slope);

	// term1 = slope / (factor + 1) * pow(-x2, factor + 1);
	// term1c = y2 * x2;
	// term2 = slope / (factor + 1) * pow(-x1, factor + 1);
	// term2c = y2 * x1;

	// term1 = slope / (factor + 1) * pow(x2, factor + 1);
	// term2 = slope / (factor + 1) * pow(x1, factor + 1);
	// term1 += term1c;
	// term2 += term2c;
	// result = term1 - term2;

    // }
    term1 += term1c;
    term2 += term2c;
    result = term1 - term2;
    // printf("weight %f\n", result);
    return result;
}


float position(float x1, float x2, float factor, float y1, float y2) {
    float fraction = (x2 - x1) / (factor + 2);
    // printf("x1: %0.2f, x2: %.2f\n", x1, x2);
    // printf("fraction: %.2f\n", fraction);
    float position;
    if (y1 < y2) {
	position = x2 - fraction;
    } else if (y1 > y2) {
	position = x1 + fraction;
    } else {
	position = (x1 + x2) / 2;
    }
    // printf("position %f\n", position);
    return position;
}
