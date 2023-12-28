#ifndef MATHS_H
#define MATHS_H

#include "../core/types.h"


vect2df getNormalizedVect(vect2df vVect);
float lerpf(float a, float b, float coef);
int minInt(int a, int b);
int maxInt(int a, int b);
float minf(float a, float b);
float maxf(float a, float b);
vect2df vectfSub(vect2df v1, vect2df v2);

#endif
