/**
 * Author: Pasquale Bianco (whiitex)
 * Date: 2025-11-08
 * License: CC0
 * Source: me
 * Description: functions for angles in 2D geometry.
 * Status: Used, works well
 */
#pragma once

// smaller angle in B in radians [0, π)
const double PI = acos(-1.0);
template<class P> double angle3pt(P a, P b, P c) {
	double dotp = (a-b).dot(c-b);
	double crsp = (a-b).cross(c-b);
	return fabs(atan2(crsp, dotp)); // [0, π]
}
// comparator sorting angles ccw wrt to (0,0)
template <class P> bool half(const P &p) { 
	return (p.y > 0 || (p.y == 0 && p.x > 0)); }
template <class P> bool cmp(const P &a, const P &b) {
	bool ha = half(a), hb = half(b);
	return (ha != hb) ? ha > hb : a.cross(b) > 0;
}
