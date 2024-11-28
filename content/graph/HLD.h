/**
 * Author: Nima Naderi
 * Date: 2024-11-28
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Code does additive modifications and max queries, but can
 * support commutative segtree modifications/queries on paths and subtrees.
 * Takes as input the full adjacency list. VALS\_EDGES being true means that
 * values are stored in the edges, as opposed to the nodes. All values
 * initialized to the segtree default. Root must be 0.
 * Time: O((\log N)^2)
 * Status: stress-tested against old HLD
 */
#pragma once

void prep(ll u, ll par){
    sub[u] ++, Par[u] = par;
    for(auto v : adj[u]){
        if(v == par) continue;
        prep(v, u);
        sub[u] += sub[v];
        if(sub[v] > sub[hvs[u]]) hvs[u] = v;
    }
}
void dfs(ll u, ll par, ll head){
    Stm[u] = ++ timer;
    hd[u] = head;
    if(hvs[u]) dfs(hvs[u], u, head);
    for(auto v : adj[u]){
        if(v == par || v == hvs[u]) continue;
        dfs(v, u, v);
    }
    Ftm[u] = timer;
}

int main(){
	while(v){
		ll c = hd[v], r = Par[c];
		now = Lazy[r] * (n - sub[c]) % Mod * invn % Mod;
		ans = (ans + now) % Mod;
		v = r;
	}
}
