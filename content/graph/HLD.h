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
        dis[v] = dis[u] + 1, prep(v, u);
        sub[u] += sub[v];
        if(sub[v] > sub[hvs[u]]) hvs[u] = v;
    }
}
void dfs(ll u, ll par, ll head){
    Stm[u] = ++ timer, Tree[timer] = u;
    hd[u] = head;
    if(hvs[u]) dfs(hvs[u], u, head);
    for(auto v : adj[u]){
        if(v == par || v == hvs[u]) continue;
        dfs(v, u, v);
    }
    Ftm[u] = timer;
}
void Qry(ll u, ll v){ //u is ancestor of v
    ll ans = 0; while(hd[v] != hd[u]){
        ans += Get(Stm[hd[v]], Stm[v]);
        v = Par[hd[v]];
    }
    ans += Get(Stm[u], Stm[v]); return ans;
}
ll Geq(ll u){ //root to u query:
    ll ans = 0; while(u){
        ans += Get(Stm[hd[u]], Stm[u]);
        u = Par[hd[u]];
    }
    return ans;
}
ll LCA(ll u, ll v){
    while(hd[u] != hd[v]){
        if(dis[hd[u]] > dis[hd[v]]) swap(u, v);
        v = Par[hd[v]];
    }
    if(dis[u] > dis[v]) swap(u, v);
    return u;
}
