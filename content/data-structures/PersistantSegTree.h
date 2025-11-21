/**
 * Author: Nima Naderi
 * Date: 2025-11-21
 * Source: My brain
 * Description: Persistant segtree, with having times of queries
 * Time: O(NlogN).
 * Status: tested
 */
#pragma once
const ll LOG = 17;
const ll MXS = MXN * 4 * LOG;
struct DATA{
    int ans;
    DATA(){ ans = 0; }
};
DATA Merge(const DATA& a, const DATA& b){}
ll n, ts, ort, Root[MXN]; //MXN refers to different time slots
DATA seg[MXS]; int LC[MXS], RC[MXS];
ll New(ll id){
    ll nd = ++ ts;
    LC[nd] = LC[id], RC[nd] = RC[id], seg[nd] = seg[id];
    return nd;
}
ll Build(ll s = 1, ll e = n){
    ll nd = New(0);
    if(ln == 1){ seg[nd].sz = 1; return nd; }
    LC[nd] = Build(s, md), RC[nd] = Build(dm, e);
    seg[nd] = Merge(seg[LC[nd]], seg[RC[nd]]);
    return nd;
}
ll Upd(ll p, ll id = ort, ll s = 1, ll e = n){
    ll nd = New(id);
    if(ln == 1){ /* update node part */
        seg[nd].ans = 1; return nd;
    }
    if(p <= md) LC[nd] = Upd(p, LC[id], s, md);
    else        RC[nd] = Upd(p, RC[id], dm, e);
    seg[nd] = Merge(seg[LC[nd]], seg[RC[nd]]);
    return nd;
}
DATA Get(ll l, ll r, ll id, ll s = 1, ll e = n){
    if(l <= s && e <= r) return seg[id];
    if(r <= md) return Get(l, r, LC[id], s, md);
    if(l >= dm) return Get(l, r, RC[id], dm, e);
    return Merge(Get(l, r, LC[id], s, md), Get(l, r, RC[id], dm, e));
}
int main(){
    ort = Root[1] = Build(); //Build the base
    vector<ll> Qry[MXN]; rep(i, 1, n){
        for(auto X: Qry[i]) ort = Upd(X);
        Root[i] = ort; //Save root at spesific times
    }
    // Solution: Binary search on the timeline
    //if(Get(l, r, Root[mid]).ans >= k)
    //Idea: Somtimes Binary search on segment tree is possible
}