#include <stdio.h>
#include <math.h>


/* float weight(float x1, float x2, float factor, float y1, float y2, float slope, int pos) {
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
} */

float area(float x1, float x2, float y1, float slope) {
    // printf("slope: %f\n", slope);
    float y2 = slope * (x2-x1) + y1;
    if (y1 > y2) {
	float tempy = y1 - y2;
	float triA = tempy * (x2 - x1) * 0.5;
	float baseA = y2 * (x2 - x1);
	float totA = triA + baseA;
	// printf("-x1: %f, x2: %f, y1: %f, y2: %f, baseA: %f, triA: %f, ty: %f\n", x1, x2, y1, y2, baseA, triA, tempy);
	return totA;
    } else if (y1 < y2){
	float tempy = y2 - y1;
	float triA = tempy * (x2 - x1) * 0.5;
	float baseA = y1 * (x2 - x1);
	float totA = triA + baseA;
	// printf("+x1: %f, x2: %f, y1: %f, y2: %f, baseA: %f, triA: %f, ty: %f\n", x1, x2, y1, y2, baseA, triA, tempy);
	return totA;
    } else {
	return y1 * (x2 - x1);
    }
}

float location(float x1, float x2, float y1, float slope) {
    float y2 = slope * (x2-x1) + y1;
    float baseP = 1.0/2.0;
    float triA, triP, baseA;
    if (y1 > y2) {
	float tempy = y1 - y2;
	triA = tempy * (x2 - x1) * 0.5;
	baseA = y2 * (x2 - x1);
	triP = 1.0/3.0;
	// printf("triA: %f, triP: %f, baseA: %f, baseP: %f\n", triA, triP, baseA, baseP);
    } else if (y1 < y2){ 
	float tempy = y2 - y1;
	triA = tempy * (x2 - x1) * 0.5;
	baseA = y1 * (x2 - x1);
	triP = 2.0/3.0;
    } else {
	return (x2 - x1) / 2;
    }
    float totA = triA + baseA;
    float xbar =(triA * triP + baseA * baseP) / totA; 
    float loc =xbar * (x2 - x1) + x1; 
    // printf("x1: %f, x2: %f, y1: %f, y2: %f, baseA: %f, triA: %f\n", x1, x2, y1, y2, baseA, triA);
    // printf("loc: %f\n", loc);
    return loc;
}


/* float position(float x1, float x2, float factor, float y1, float y2, float slope) {
    float fraction = (x2 - x1) / (factor + 2);
    // printf("%f\n", factor+2);
    float base_frac = (x2 - x1) / 2;
    // printf("x1: %0.2f, x2: %.2f\n", x1, x2);
    // printf("fraction: %.2f\n", fraction);
    float position;
    if (y1 < y2) {
	printf("x1: %.2f, x2: %.2f, y1: %.2f, y2: %.2f\n", x1, x2, y1, y2);
	float a1 = weight(x1, x2, factor, y1, y2, slope, 1);
	float a2 = (x2 - x1) * y1;
	position = x2 - fraction;
	// position = (fraction * a1 + base_frac * a2) / (a1 + a2);
    } else if (y1 > y2) {
	// fraction = x1 + fraction;
	float tx1 = pow((y1-y2)/-slope, 1/factor);
	float tx2 = tx1 - x2;
	float low_y = -slope * pow(tx2, factor) + y2;
	float a1 = weight(x1, x2, factor, y1-low_y, 0,  slope, 1);
	printf("lowy %f\n", low_y);
	float a2 = (tx1 - tx2) * low_y;
	printf("x1: %.2f, x2: %.2f, y1: %.2f, y2: %.2f\n", x1, x2, y1, y2);
	printf("a1: %f a2: %f\n", a1, a2);
	printf("sum A %f\n", a1+a2);
	position = (fraction * a1 + base_frac * a2) / (a1 + a2);
    } else {
	position = (x1 + x2) / 2;
    }
    printf("position %f\n", position);
    return position;
} */
