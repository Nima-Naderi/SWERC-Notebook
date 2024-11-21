/**
 * Author: Nima Naderi Ghotbodini
 * Date: 2024-11-21
 * Source: https://github.com/Nima-Naderi/Algonima/blob/master/Strings/palindrome_hash.cpp
 * Description: Checking if the string is palindrome
 * Status: Tested on codeforces
 */
#pragma once

ll n; string s; //! Length is important in RH!
ll pw[MXH][MXN], H[MXH][MXN], RH[MXH][MXN];
void InitPow(){ //RH: ith suffix Hash, i <-> n - i + 1
	for(int th = 0; th < MXH; th ++){
		pw[th][0] = 1;
		for(int i = 1; i < MXN; i ++) pw[th][i] = pw[th][i - 1] * BASE % Mod[th];
	}
}
void InitHash(){
	assert(s[0] == '$' && s.size() == n + 1);
	for(int th = 0; th < MXH; th ++){
		H[th][0] = RH[th][0] = 0;
		for(int i = 1; i <= n; i ++){
			H[th][i] = (H[th][i - 1] * BASE + (s[i] - 'a' + 1)) % Mod[th];
			RH[th][i] = (RH[th][i - 1] * BASE + (s[n - i + 1] - 'a' + 1)) % Mod[th];
		}
	}
}
inline ll Hash(int th, ll l, ll r){
	return (H[th][r] - H[th][l - 1] * pw[th][r - l + 1] % Mod[th] + Mod[th]) % Mod[th];
}
inline ll RHash(int th, ll l, ll r){
	// H(l, r) -> H[l] - H[r + 1] * pw[len]
	return (RH[th][n - l + 1] - RH[th][n - (r + 1) + 1] * pw[th][r - l + 1] % Mod[th] + Mod[th]) % Mod[th];
}
inline ll IsPal(ll l, ll r){
	for(int th = 0; th < MXH; th ++)
		if(Hash(th, l, r) != RHash(th, l, r))
			return 0;
	return 1;
}
