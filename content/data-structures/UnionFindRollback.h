/**
 * Author: Lukas Polacek, Simon Lindholm
 * Date: 2019-12-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure with undo.
 * If undo is not needed, skip st, time() and rollback().
 * Usage: int t = uf.time(); ...; uf.rollback(t);
 * Time: $O(\log(N))$
 * Status: tested as part of DirectedMST.h
 */
#pragma once

ll Par[MXN], Sz[MXN]; vector<ll> hist;
ll Find(ll x){ return (Par[x] == x ? x : Find(Par[x])); }
bool Union(ll x, ll y){
    x = Find(x), y = Find(y);
    if(x == y) return 0;
    if(Sz[x] < Sz[y]) swap(x, y);
    Par[y] = x, Sz[x] += Sz[y];
    hist.push_back(y);
    return 1;
}
void Undo(){
    ll x, y = hist.back();
    x = Par[y], hist.pop_back();
    Sz[x] -= Sz[y], Par[y] = y;
}
//iota(Par, Par + n + 1, 0);
//fill(Sz, Sz + n + 1, 1);
