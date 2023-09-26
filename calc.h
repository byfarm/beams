#include <stdio.h>
#include <math.h>


float weight(float x1, float x2, float factor, float y1, float y2, float slope, int pos) {
    if (fabsf(slope) < 0.01 | fabsf(factor) <= 0.01) {
	float result = (x2 - x1) * y1;
	// printf("weight c %f\n", result);
	return result;
    }
    // printf("slope: %0.2f\n", slope);
    float term1, term2, term1c, term2c, result;
    if (slope > 0) {
	term1 = slope / (factor + 1) * pow(x2, factor + 1);
	term2 = slope / (factor + 1) * pow(x1, factor + 1);
	term1c = y1 * x2;
	term2c = y1 * x1;
    } else {
	// slope = -slope;
	// term1c = y2 * x2;
	// term2c = y2 * x1;
	// slope = -slope;

	slope = -slope;
	// printf("slope: %0.2f\n", slope);
	x1 = pow((y1-y2)/slope, 1/factor);
	x2 = x1 - x2;
	// printf("x1: %.2f, x2: %.2f, y1: %.2f, y2: %.2f\n", x1, x2, y1, y2);
	term2 = slope / (factor + 1) * pow(x2, factor + 1);
	term1 = slope / (factor + 1) * pow(x1, factor + 1);
	term2c = y2 * x2;
	term1c = y2 * x1;
	if (pos) {
	    term2c *= x2;
	    term1c *= x1;
	}
	
	// term2 = slope / (factor + 1) * pow(-(x2-y1), factor + 1);
	// term2c = y1 * -(x2-y1);
	// term2c = 0;
	// term1 = slope / (factor + 1) * pow(-(x1-y1), factor + 1);
	// term1c = y2 * -(x1-y1);
	// term1c = 0;

	// term1 = slope / (factor + 1) * pow(x2, factor + 1);
	// term2 = slope / (factor + 1) * pow(x1, factor + 1);
	// term1 += term1c;
	// term2 += term2c;
	// result = term1 - term2;

    }
    term1 += term1c;
    term2 += term2c;
    result = term1 - term2;
    // printf("weight %f\n", result);
    return result;
}


float position(float x1, float x2, float factor, float y1, float y2, float slope) {
    float fraction = (x2 - x1) / (factor + 2);
    // printf("%f\n", factor+2);
    float base_frac = (x2 - x1) / 2;
    float a1 = weight(x1, x2, factor, y1, y2, -0.9, 1);
    float a1x = weight(x1, x2, factor+1, y1, y2, -0.9, 1);
    float xbar = a1x/a1;
    printf("xbar: %.2f\n", xbar);
    // printf("x1: %0.2f, x2: %.2f\n", x1, x2);
    // printf("fraction: %.2f\n", fraction);
    float position;
    
    if (y1 < y2) {
	float a2 = (x2 - x1) * y1;
	fraction = x2 - fraction;
	position = (fraction * a1 + base_frac * a2) / (a1 + a2);
    } else if (y1 > y2) {
	a1 = weight(x1, x2, factor, y1-y2, 0, slope, 1);
	x1 = pow((y1-y2)/-slope, 1/factor);
	x2 = x1 - x2;
	float low_y = -slope * pow(x2, factor) + y2;
	printf("lowy %f\n", low_y);
	float a2 = (x1 - x2) * low_y;
	printf("x1: %.2f, x2: %.2f, y1: %.2f, y2: %.2f\n", x1, x2, y1, y2);
	printf("a1: %f a2: %f\n", a1, a2);
	// fraction = x1 + fraction;
	position = (fraction * a1 + base_frac * a2) / (a1 + a2);
    } else {
	position = (x1 + x2) / 2;
    }
    printf("position %f\n", position);
    return position;
}
