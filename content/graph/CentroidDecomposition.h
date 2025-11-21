/**
 * Author: Nima Naderi
 * Date: 2025-11-21
 * Source: my brain
 * Description: Centroid decomposition
 * Time: O(NlgN)
 * Usage: DMS(1, 0);
 * Status: test
 */
#pragma once
ll n, Mod, ans, phi;
ll sub[MXN], dis[MXN], Val[MXN];
vector<pair<ll, ll>> adj[MXN];
bool hide[MXN]; unordered_map<int, int> Cnt;
void plant(ll u, ll par){
    sub[u] = 1;
    for(auto Pr : adj[u]){
        ll v = Pr.first;
        if(v != par && !hide[v]){
            plant(v, u), sub[u] += sub[v];
        }
    }
}
void Pre(ll u, ll par){
    if(par == -1) Val[u] = dis[u] = 0;
    for(auto Pr : adj[u]){
        ll v, w; tie(v, w) = Pr;
        if(v != par && !hide[v]){
            Val[v] = (Val[u] + pw[dis[u]] * w % Mod) % Mod;
            dis[v] = dis[u] + 1;
            Pre(v, u);
        }
    }
}
void Upd(ll u, ll par, ll dt){
    Cnt[Val[u]] += dt;
    for(auto Pr : adj[u]){
        ll v = Pr.first;
        if(v != par && !hide[v]) Upd(v, u, dt);
    }
}
void Calc(ll u, ll par, ll now){
    ll goal = Mod - (now * ipw[dis[u]] % Mod);
    if(goal == Mod) goal = 0;
    if(Cnt.count(goal)) ans += Cnt[goal];
    for(auto Pr : adj[u]){
        ll v, w; tie(v, w) = Pr;
        if(v != par && !hide[v]){
            Calc(v, u, (now * 10ll % Mod + w) % Mod);
        }
    }
}
ll CRD(ll u, ll par, ll val){
    for(auto Pr : adj[u]){
        ll v = Pr.first;
        if(v == par || hide[v]) continue;
        if(sub[v] >= val) return CRD(v, u, val);
    }
    return u;
}
void DMS(ll u, ll h){
    plant(u, -1);
    ll cent = CRD(u, -1, (sub[u] + 1) / 2); //attention
    Pre(cent, -1), Upd(cent, -1, 1);
    for(auto Pr : adj[cent]){
        ll v, w; tie(v, w) = Pr;
        if(hide[v]) continue;
        Upd(v, cent, -1);
        Calc(v, cent, w);
        Upd(v, cent, +1);
    }
    Cnt[Val[cent]] --;
    ans += Cnt[0];
    Cnt.clear();
    hide[cent] = 1;
    for(auto Pr : adj[cent]){
        ll v = Pr.first;
        if(!hide[v]) DMS(v, h + 1);
    }
}