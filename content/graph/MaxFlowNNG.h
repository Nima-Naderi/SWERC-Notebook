/**
 * Author: Nima Naderi Ghotbodini
 * Date: 2024-11-28
 * Source: https://codeforces.com/contest/1783/submission/262399440
 * Description: Maxflow
 * Time: $O(F E \log(V))$ where F is max flow. $O(VE)$ for setpi.
 */
#pragma once

struct MaxFlow {
	struct Edge {
		int fr, to; ll cp, fl;
	};
	int n, src, snk; ll D;
	vector<Edge> E;
	vector<int> adj[maxn];
	int cnt[maxn]; ll dis[maxn];
	queue<int> qu;
	void init(int sz, int v1, int v2) {
		E.clear();
		n = sz; src = v1; snk = v2;
		for (int i = 0; i < n; i++) adj[i].clear();
	}
	void addEdge(int u, int v, ll cp) {
		adj[u].pb(len(E)); E.pb({u, v, cp, 0});
		adj[v].pb(len(E)); E.pb({v, u, 0, 0});
	}
	bool bfs() {
		int v = src;
		fill(dis, dis + n, oo); fill(cnt, cnt + n, 0);
		dis[v] = 0; qu.push(v);
		while (!qu.empty()) {
			int v = qu.front(); qu.pop();
			for (int j : adj[v]) {
				int u = E[j].to; ll cp = E[j].cp, fl = E[j].fl, rm = cp - fl;
				if (rm < D) continue;
				if (dis[v] + 1 < dis[u]) {
					dis[u] = dis[v] + 1;
					qu.push(u);
				}
			}
		}
		return (dis[snk] < oo);
	}
	ll dfs(int v, ll f) {
		if (f < D) f = 0;
		if (v == snk || f == 0) return f;
		
		ll res = 0;
		for (; cnt[v] < len(adj[v]); cnt[v]++) {
			int j = adj[v][cnt[v]];
			int u = E[j].to; ll cp = E[j].cp, fl = E[j].fl, rm = cp - fl;
			if (dis[v] + 1 != dis[u]) continue;
			
			int x = dfs(u, min(f, rm));
			res += x; f -= x;
			E[j].fl += x; E[j ^ 1].fl -= x;
			if (f == 0) break;
		}
		return res;
	}
	ll dinic() {
		ll res = 0; D = 1;
		while (D > 0) {
			while (bfs()) res += dfs(src, INF);
			D /= 2;
		}
		return res;
	}
};
MaxFlow A;
int main(){
    A.init(c1 + c2 + 2, c1 + c2, c1 + c2 + 1);
	for (int i = 0; i < c1; i++) A.addEdge(A.src, i, 1);
	for (int i = c1; i < c1 + c2; i++) A.addEdge(i, A.snk, 1);
	for (int i = 0; i < n; i++) {
		int u = col1[i], v = c1 + col2[i];
		ind[i] = len(A.E); A.addEdge(u, v, 1);
	}
	cout << n - A.dinic() << endl;
	return 0;
}