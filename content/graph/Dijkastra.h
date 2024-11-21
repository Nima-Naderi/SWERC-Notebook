/**
 * Author: Nima Naderi Ghotbodini
 * Date: 2024-11-21
 * Source: https://github.com/Nima-Naderi/Algonima/blob/master/Graphs/dijkastra.cpp
 * Description: single/multisource dijakstra
 * Status: Tested on codeforces
 */
#pragma once

ll dis[MXN]; bool vis[MXN]; //pll adj vector
priority_queue<pll, vector<pll>, greater<pll>> pq;
inline ll Dijk(ll src = 0, ll sink = 0){
	if(src){
		for(int i = 1; i <= n; i ++) dis[i] = INF, vis[i] = 0;
		pq.push(Mp(dis[src] = 0, src));
	} else { //multi-source dijkastra
		for(int u = 1; u <= n; u ++) pq.push(Mp(dis[u], u));
	}
	while(!pq.empty()){
		ll u, d; tie(d, u) = pq.top(); pq.pop();
		if(vis[u]) continue;
		if(u == sink) return d;
		vis[u] = 1;
		for(auto e : adj[u]){
			ll v, w; tie(v, w) = e;
			if(!vis[v] && d + w < dis[v]){
				pq.push(Mp(dis[v] = d + w, v));
			}
		}
	}
	return -1;
}
