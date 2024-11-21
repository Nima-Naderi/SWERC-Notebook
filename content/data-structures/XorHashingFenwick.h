/**
 * Author: Nima Naderi Ghotbodini
 * Date: 2024-11-21
 * Source: https://github.com/Nima-Naderi/Algonima/blob/master/DataStructures/xor_hashing_fenwick.cpp
 * Description: Random number generators and fenwick on it with xor.
 * Status: Tested on codeforces
 */
#pragma once

const ll MXN = 3e5 + 10;
const ll MXK = 32; //16
//Random number generation (64 bits is safe):
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937 Rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
// mt19937 rng(time(0));
// srand(time(0)); srand(time(NULL));

typedef unsigned long long u64;
const valarray<u64> zero(0ull, MXK);

static uint64_t hsh(uint64_t x){
	// http://xorshift.di.unimi.it/splitmix64.c
	x += 0x9e3779b97f4a7c15;
	x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
	x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
	return x ^ (x >> 31);
}
valarray<u64> to_arr(u64 x){
	static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
	x += FIXED_RANDOM;
	valarray<u64> ans(0ull, MXK);
	for(ll i = 0; i < MXK; i ++)
		ans[i] = hsh(x + i * i * i + i) % (1ull << 32);
	return ans;
}

valarray<u64> Fen[MXN];
inline void initFen(){ //boundry can be n itself
	for(int i = 0; i < MXN; i ++) Fen[i] = zero;
}
void Upd(ll p, valarray<u64> x){
    for(; p < MXN; p += p & -p) Fen[p] += x;
}
valarray<u64> Get(ll p){
    valarray<u64> s(0ull, MXK); for(; p; p -= p & -p) s += Fen[p]; return s;
}

ll n;
valarray<u64> A[MXN];

struct ValarrayComparator {
    bool operator()(const valarray<u64>& a, const valarray<u64>& b) const {
		assert(a.size() == MXK && b.size() == MXK);
        for(size_t i = 0; i < MXK; ++ i){
            if(a[i] != b[i]) return a[i] < b[i]; 
        }
        return false;
    }
}; //Check mod k for understanding if it appeared kt times
map<valarray<u64>, ll, ValarrayComparator> mp;

int32_t main(){
	initFen();
	cin >> n;
	for(int i = 1; i <= n; i ++){
		ll x; cin >> x;
		A[i] = to_arr(x); //auto y = ..
	}
}
