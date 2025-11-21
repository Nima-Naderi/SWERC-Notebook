/**
 * Author: Nima Naderi Ghotbodini
 * Date: 2024-11-21
 * Source: https://github.com/Nima-Naderi/Algonima/blob/master/NumberTheory/sieve.cpp
 * Description: Prime sieve for generating all primes up to a certain limit.
 * Status: Tested on codeforces
 */
#pragma once

ll pt; vector<ll> lpf, Prm, prm;
inline void Sieve(ll m){ //maximum value in inputs
    lpf.assign(m + 1, 0);
    for(int i = 2; i <= m; i ++){
        if(!lpf[i]) Prm.push_back(lpf[i] = i);
        for(int p : Prm){
            if(p > lpf[i] || p * i > m) break;
            lpf[p * i] = p;
        }
    }
	pt = Prm.size();
}
inline void factorize(ll num){
	prm.clear();
    for(int x = num, p = lpf[x]; x > 1; prm.push_back(p), p = lpf[x]){
        while(x % p == 0) x /= p;
    }
}
inline void GetPresentPrimes(){
	Prm.clear();
	for(int i = 1; i <= n; i ++){
		factorize(A[i]);
		for(auto X : prm) Prm.push_back(X);
	}
	sort(Prm.begin(), Prm.end());
    Prm.resize(pt = (unique(Prm.begin(), Prm.end()) - Prm.begin()));
}
inline int GetPrmId(ll x){
    return lower_bound(Prm.begin(), Prm.end(), x) - Prm.begin() + 1;
}