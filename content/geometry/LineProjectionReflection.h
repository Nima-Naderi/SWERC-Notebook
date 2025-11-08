/**
 * Author: Pasquale Bianco (whiitex)
 * Date: 2025-11-08
 * License: CC0
 * Description: Projects point p onto line ab. Set refl=true to get reflection
 * of point p across line ab instead. Products of three coordinates are used 
 * in intermediate steps so watch out for overflow.
 * Status: used, works well
 */
#pragma once

#include "Point.h"

// projection of point p on line ax + by + c = 0
template<class P> P projOnLine(P p, dbl a, dbl b, dbl c) {
	double d = (a * p.x + b * p.y + c) / (a*a + b*b);
	return {p.x - a * d, p.y - b * d};
}
// projection of point p on line defined by points a and b
template<class P> P projOnLine(P p, P a, P b) {
	P ab = b - a;
	double t = (p - a).dot(b-a) / ab.dot(b-a);
	return a + ab * t;
}
// reflection of point p over line defined by points a and b
template<class P> P reflectOverLine(P p, P a, P b) {
    P proj = projOnLine(p, a, b);
    return proj * 2 - p;
}