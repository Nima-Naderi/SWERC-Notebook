/**
 * Author: Nima Naderi Ghotbodini
 * Date: 2024-11-28
 * Source: https://codeforces.com/contest/163/submission/108176654
 * Description: Aho-Corasick automaton, used for multiple pattern matching.
 * Initialize with AhoCorasick ac(patterns); the automaton start node will be at index 0.
 * find(word) returns for each position the index of the longest word that ends there, or -1 if none.
 * findAll($-$, word) finds all words (up to $N \sqrt N$ many if no duplicate patterns)
 * that start at each position (shortest first).
 * Duplicate patterns are allowed; empty patterns are not.
 * To find the longest words that start at each position, reverse all input.
 * For large alphabets, split each symbol into chunks, with sentinel bits for symbol boundaries.
 * Time: construction takes $O(26N)$, where $N =$ sum of length of patterns.
 * find(x) is $O(N)$, where N = length of x. findAll is $O(NM)$.
 * Status: Tested on codeforces
 */
#pragma once

const ll SGM = 26;
int n, q, ts = 1, timer;
int Q[MXN], Ver[MXN], seg[MXS], Lazy[MXS];
int nxt[MXN][SGM], lps[MXN];
char s[MXN];
void Add(int id){
    scanf("%s", s); int sz = strlen(s);
    int u = 1;
    for(int h = 0; h < sz; h ++){
        if(!nxt[u][s[h] - 'a']) nxt[u][s[h] - 'a'] = ++ ts;
        u = nxt[u][s[h] - 'a'];
    }
    Ver[id] = u;
}
void Aho(){
    int L = 0, R = 0;
    for(int i = 0; i < SGM; i ++){
        if(!nxt[1][i]) nxt[1][i] = 1;
        else{
            Q[R ++] = nxt[1][i];
            lps[nxt[1][i]] = 1;
        }
    }
    while(L < R){
        int u = Q[L ++];
        adj[lps[u]].push_back(u);
        for(int c = 0; c < SGM; c ++){
            if(!nxt[u][c]) nxt[u][c] = nxt[lps[u]][c];
            else{
                lps[nxt[u][c]] = nxt[lps[u]][c];
                Q[R ++] = nxt[u][c];
            }
        }
    }
}
void dfs(int u, int par){
    Stm[u] = ++ timer;
    for(auto v : adj[u]){
        if(v == par) continue;
        dfs(v, u);
    } Ftm[u] = timer;
}
void Shift(int id, int s, int e){
    if(!Lazy[id]) return;
    seg[id] += Lazy[id] * ln;
    if(ln > 1){
        Lazy[lc] += Lazy[id];
        Lazy[rc] += Lazy[id];
    }
    Lazy[id] = 0;
}
void Upd(int l, int r, int x, int id = 1, int s = 1, int e = ts){
    Shift(id, s, e);
    if(e < l || s > r) return;
    if(l <= s && e <= r){
        Lazy[id] += x; Shift(id, s, e);
        return;
    }
    Upd(l, r, x, lc, s, md), Upd(l, r, x, rc, dm, e);
    seg[id] = seg[lc] + seg[rc];
}
ll Get(int p, int id = 1, int s = 1, int e = ts){
    Shift(id, s, e);
    if(ln == 1) return seg[id];
    if(p <= md) return Get(p, lc, s, md);
    return Get(p, rc, dm, e);
}

int main(){
    scanf("%d%d", &q, &n); for(int i = 1; i <= n; i ++) Add(i);
    Aho();
    dfs(1, 0); assert(timer == ts);
    for(int i = 1; i <= n; i ++){
        Upd(Stm[Ver[i]], Ftm[Ver[i]], +1);
    }
    while(q --){
		ll Now = 0, ans = 1;
		scanf("%s", s); len = strlen(s);
		for(int i = 0; i < len; i ++){
			ans = nxt[ans][s[i] - 'a'];
			Now += Get(Stm[ans]);
		} printf("%lld\n", Now);
    }
}