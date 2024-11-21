/**
 * Author: Nima Naderi Ghotbodini
 * Date: 2024-11-21
 * Source: https://github.com/Nima-Naderi/Algonima/blob/master/FFT/ntt.cpp
 * Description: ntt(a) computes $\hat f(k) = \sum_x a[x] g^{xk}$ for all $k$, where $g=\text{root}^{(mod-1)/N}$.
 * N must be a power of 2.
 * Useful for convolution modulo specific nice primes of the form $2^a b+1$,
 * where the convolution result has size at most $2^a$. For arbitrary modulo, see FFTMod.
   \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$.
   For manual convolution: NTT the inputs, multiply
   pointwise, divide by n, reverse(start+1, end), NTT back.
 * Inputs must be in [0, mod).
 * Time: O(N \log N)
 * Status: tested on CodeForces
 */
#pragma once

#include "../number-theory/ModPow.h"

const ll mod = (119 << 23) + 1, root = 62; // = 998244353
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
ll rev[MXF];
const ll iMXF = inv(MXF);
void NTT(ll *A, bool inverse = 0){
	for(int i = 1; i < MXF; i ++){
		rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (LOG - 1)));
		if(rev[i] < i) swap(A[i], A[rev[i]]);
	}
	for(int l = 1; l < MXF; l <<= 1){
		ll wn = power(3, Mod / 2 / l); // 3 or 5
		if(inverse) wn = inv(wn);
		for(int i = 0; i < MXF; i += (l << 1)){
			ll w = 1;
			for(int j = i; j < i + l; j ++){
				ll v = A[j], u = w * A[j + l] % Mod;
				mkay(A[j] = u + v);
				mkay(A[j + l] = v - u);
				w = w * wn % Mod;
			}
		}
	}
	if(!inverse) return;
	for(int i = 0; i < MXF; i ++) A[i] = A[i] * iMXF % Mod;
}
