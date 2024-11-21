/**
 * Author: Nima Naderi Ghotbodini
 * Date: 2024-11-21
 * Source: https://github.com/Nima-Naderi/Algonima/blob/master/Graphs/lca.cpp
 * Description: Data structure for computing lowest common ancestors in a tree
 * Time: $O(N \log N + Q)$
 * Status: tested on codeforces
 */
#pragma once

#include "../data-structures/RMQ.h"

ll Jad[LOG][MXN], dis[MXN];
void prep(ll u, ll par){
	Jad[0][u] = par;
	for(int i = 1; i < LOG; i ++){
		Jad[i][u] = Jad[i - 1][Jad[i - 1][u]];
	}
	for(auto v : adj[u]){
		if(v == par) continue;
		dis[v] = dis[u] + 1;
		prep(v, u);
	}
}
ll K_Jad(ll u, ll k){
	for(int i = 0; i < LOG; i ++){
		if((k >> i) & 1LL) u = Jad[i][u];
	}
	return u;
}
ll LCA(ll u, ll v){
	if(dis[v] < dis[u]) swap(u, v);
	v = K_Jad(v, dis[v] - dis[u]);
	if(u == v) return u;
	for(int i = LOG - 1; ~i; i --){
		if(Jad[i][u] != Jad[i][v]) u = Jad[i][u], v = Jad[i][v];
	}
	return Jad[0][u];
}
inline ll Distance(ll u, ll v){
	return dis[u] + dis[v] - 2 * dis[LCA(u, v)];
}
