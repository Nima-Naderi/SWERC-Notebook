/**
 * Author: Pasquale Bianco (whiitex)
 * Date: 2025-11-08
 * License: MIT
 * Source: https://cp-algorithms.com/geometry/minkowski.html
 * Description: Minkowski sum of two convex polygons.
 * Make sure both polygons have at least 2 points !!!!!
 * Time: O(n + m)
 * Status: tested
 */
#pragma once

#include "Point.h"

template<class T> void reorder_polygon(vector<T> &P) {
	size_t pos = 0;
	for (size_t i = 1; i < P.size(); i++) {
		if (P[i].y < P[pos].y || 
			(P[i].y == P[pos].y && P[i].x < P[pos].x))
			pos = i;
	} rotate(P.begin(), P.begin() + pos, P.end());
}
template<class T> vector<T> Mink(vector<T> P, vector<T> Q) {
	reorder_polygon(P); reorder_polygon(Q);
	P.push_back(P[0]); P.push_back(P[1]);
	Q.push_back(Q[0]); Q.push_back(Q[1]);
	vector<T> result; size_t i = 0, j = 0;
	while (i < P.size() - 2 || j < Q.size() - 2) {
		result.push_back(P[i] + Q[j]);
		auto cross = (P[i + 1] - P[i]).cross(Q[j + 1] - Q[j]);
		if (cross >= 0 && i < P.size() - 2) ++i;
		if (cross <= 0 && j < Q.size() - 2) ++j;
	} return result;
}