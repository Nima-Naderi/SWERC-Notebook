/**
 * Author: Nima Naderi
 * Date: 2025-11-21
 * Source: my brain
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Time: O(NlogN).
 * Status: tested
 */
#pragma once
#define lc (id * 2)
#define rc (id * 2 + 1)
#define ln (e - s + 1)
#define md ((s + e) / 2)
#define dm ((s + e) / 2 + 1)
const ll MXS = MXN * 4 + 10;
ll n, q, A[MXN], seg[MXS];
ll Max[MXS], Min[MXS], lazySet[MXS], lz[MXS];
void Build(ll id = 1, ll s = 1, ll e = n){
	if(ln == 1){ /* something */ return; }
	Build(lc, s, md), Build(rc, dm, e);
    // merge
}
void Shift(ll id = 1, ll s = 1, ll e = n){
	if(!lz[id]) return;
    //apply lazy
    if(ln > 1){ lz[lc] += lz[id], lz[rc] += lz[id]; }
    lz[id] = 0;
}
void Upd(ll l, ll r, ll x, ll id = 1, ll s = 1, ll e = n){
	Shift(id, s, e);
	if(e < l || s > r) return;
	if(l <= s && e <= r /*&& Max[id] == Min[id]*/){ 
		lz[id] = x; Shift(id, s, e); return;
	}
	Upd(l, r, x, lc, s, md), Upd(l, r, x, rc, dm, e);
	// merge
}
ll Get(ll l, ll r, ll id = 1, ll s = 1, ll e = n){
	Shift(id, s, e);
	if(e < l || s > r) return 0; // Null
	if(l <= s && e <= r) return seg[id];
	return Get(l, r, lc, s, md) + Get(l, r, rc, dm, e);
}
