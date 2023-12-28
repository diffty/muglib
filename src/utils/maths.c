#include "maths.h"


vect2df getNormalizedVect(vect2df vVect) {
	vect2df vNormalizedVect;

	if (fabs(vVect.x) < fabs(vVect.y)) {
		vNormalizedVect.x = vVect.x / fabs(vVect.y);
		vNormalizedVect.y = vVect.y / fabs(vVect.y);
	}
	else if (fabs(vVect.x) > fabs(vVect.y)) {
		vNormalizedVect.x = vVect.x / fabs(vVect.x);
		vNormalizedVect.y = vVect.y / fabs(vVect.x);
	}
	else {
		vNormalizedVect.x = vVect.x / fabs(vVect.x);
		vNormalizedVect.y = vVect.y / fabs(vVect.y);
	}

	return vNormalizedVect;
}

float lerpf(float a, float b, float coef) {
	return a + (b - a) * coef;
}

int minInt(int a, int b) {
	return (a < b) ? a : b;
}

int maxInt(int a, int b) {
	return (a >= b) ? a : b;
}

float minf(float a, float b) {
	return (a < b) ? a : b;
}

float maxf(float a, float b) {
	return (a >= b) ? a : b;
}

vect2df vectfSub(vect2df v1, vect2df v2) {
	vect2df vNewVect;
	vNewVect.x = v2.x - v1.x;
	vNewVect.y = v2.y - v1.y;

	return vNewVect;
}
