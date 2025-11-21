/**
 * Author: Nima Naderi
 * Date: 2025-11-21
 * Source: cp-algo
 * Description: inverse of x mod Mod iff gcd(Mod, x) = 1
 */
#pragma once

ll gcd(ll x, ll y){
	return (!y ? x : gcd(y, x % y));
}
// Extended euclidean algorithm - Bezout's identity
tuple<ll, ll, ll> extended_gcd(ll a, ll b){
    if(b == 0) return {a, 1, 0};
    auto [gcd, x1, y1] = extended_gcd(b, a % b);
    return {gcd, y1, x1 - (a / b) * y1};
}
ll inv(ll x, ll Mod){ // return 0 if doesn't exist
    auto [g, ix, _] = extended_gcd(x, Mod);
    if (g != 1) return 0;
	return (ix % Mod + Mod) % Mod;
}
void init(){ //inverse of x mod Mod
    ll p = 2, m = Mod; phi = m;
    while(p * p <= m){
        if(m % p == 0){
            while(m % p == 0) m /= p;
            phi -= phi / p;
        }
        p ++;
    }
    if(m > 1) phi -= phi / m;
    ll x = 10, inv_x = power(x, phi - 1); 
}
