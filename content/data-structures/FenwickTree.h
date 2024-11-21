/**
 * Author: Nima Naderi Ghotbodini
 * Date: 2024-11-21
 * Source: https://github.com/Nima-Naderi/Algonima/blob/master/DataStructures/fenwick_tree.cpp
 * Description: Computes partial sums
 * Time: $O(\log N)$.
 * Status: Tested on codeforces
 */
#pragma once

ll Fen[MXN]; //Be careful with Mod
void Upd(ll p, ll x){
    for(; p < MXN; p += p & -p) Fen[p] += x;
} // Call fill(Fen, Fen + n + 5, 0) in main
void Upd(ll l, ll r, ll x){
    Upd(l, x), Upd(r + 1, -x);
}
ll Get(ll p){
    ll s = 0; for(; p; p -= p & -p) s += Fen[p]; return s;
}
ll Get(ll l, ll r){
    return (r < l ? 0 : Get(r) - Get(l - 1));
}
ll Find(ll k){
    ll ans = 0;
    for(int i = LOG; ~i; i --){
        if(ans + (1LL << i) < MXN && Fen[ans + (1LL << i)] >= k){
            ans += (1LL << i), k -= Fen[ans];
        }
    }
    return ans + 1;
}
