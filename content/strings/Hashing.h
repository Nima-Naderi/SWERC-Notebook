/**
 * Author: Nima Naderi Ghotbodini
 * Date: 2024-11-21
 * Source: https://github.com/Nima-Naderi/Algonima/blob/master/Strings/double_hash.cpp
 * Description: Self-explanatory methods for string hashing.
 * Status: Tested on codeforces
 */
#pragma once

const ll MXH = 2; const ll BASE = 257;
const ll Mod[MXH] = {(ll)(1e9 + 7), (ll)(1e9 + 9)};
void mkay(int th, ll &x){
	if(x > Mod[th]){ x -= Mod[th]; }
}
ll pw[MXH][MXN], H[MXH][MXN];
void InitPow(){
	for(int th = 0; th < MXH; th ++){
		pw[th][0] = 1;
		for(int i = 1; i < MXN; i ++) pw[th][i] = pw[th][i - 1] * BASE % Mod[th];
	}
}
void InitHash(ll &n, string &s){
	assert(s[0] == '$' && s.size() == n + 1);
	for(int th = 0; th < MXH; th ++){
		H[th][0] = 0;
		for(int i = 1; i <= n; i ++){
			H[th][i] = (H[th][i - 1] * BASE + (s[i] - 'a' + 1)) % Mod[th];
		}
	}
}
inline ll Hash(int th, ll l, ll r){
	return (H[th][r] - H[th][l - 1] * pw[th][r - l + 1] % Mod[th] + Mod[th]) % Mod[th];
} // Call InitPow(), InitHash(n, s); in main
