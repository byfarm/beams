#include <stdio.h>
#include <math.h>


float weight(float x1, float x2, float factor, float y1, float y2) {
    float ydiff = y2 - y1;
    printf("ydiff %f\n", ydiff);
    if (ydiff < 0.01) {
	float result = (x2 - x1) * y1;
	printf("weight %f\n", result);
	return result;
    }
    float slope = (ydiff) / (x2 - x1); // this may lead to catestrophic canellation
    float term1 = slope / (factor + 1) * pow(x2, factor + 1);
    float term2 = slope / (factor + 1) * pow(x1, factor + 1);
    float result = term1 - term2;
    printf("weight %f\n", result);
    return result;
}


float position(float x1, float x2, float factor, float y1, float y2) {
    float fraction = fabsf(x2 - x1) / (factor + 2);
    float position;
    if (y1 < y2) {
	position = x1 + fraction;
    } else if (y1 > y2) {
	position = x1 + (1 - fraction);
    } else {
	position = (x1 + x2) / 2;
    }
    printf("position %f\n", position);
    return position;
}
