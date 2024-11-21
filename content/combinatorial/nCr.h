/**
 * Author: Nima Naderi Ghotbodini
 * Date: 2024-11-21
 * Source: github.com/Nima-Naderi/Algonima/Combinatorics/nCr.cpp
 * Description: Computes $\displaystyle \binom{n}{k}$.
 * Status: Tested on codeforces
 */
#pragma once
ll power(ll a, ll b){
	return (!b ? 1 : power(a * a % Mod, b / 2) * (b & 1LL ? a : 1) % Mod);
}
ll inv(ll x){ return power(x, Mod - 2); }
void mkay(ll &x){
	if(x < 0) x += Mod;
	if(x >= Mod) x -= Mod;
}
ll F[MXN], I[MXN];
ll nCr(ll n, ll r){
	if(r < 0 || r > n) return 0;
	return F[n] * I[r] % Mod * I[n - r] % Mod;
}
inline void Init(){
	F[0] = I[0] = 1;
	for(int i = 1; i < MXN; i ++) F[i] = F[i - 1] * i % Mod;
	I[MXN - 1] = inv(F[MXN - 1]);
	for(int i = MXN - 2; i; -- i) I[i] = I[i + 1] * (i + 1) % Mod;
} // Call Init(); in main
ll NcR(ll n, ll r){ //Iterative version
	if(r < 0 || r > n) return 0;
	ll ans = 1;
	for(ll i = n; i > n - r; -- i) ans = ans * i % Mod;
	for(ll i = 2; i <= r; i ++) ans = ans * inv(i) % Mod;
	return ans;
}
