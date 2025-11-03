/**
 * Author: Lukas Polacek
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Operators for modular arithmetic. You need to set {\tt mod} to
 * some number first and then you can use the structure.
 */
#pragma once

const ll mod = 998244353;
struct mint {
	ll x;
    mint() : x(0) {}
	mint(ll xx) : x(xx) {}
	mint operator+(mint b) { return mint((x + b.x) % mod); }
	mint operator-(mint b) { return mint((x - b.x + mod) % mod); }
	mint operator*(mint b) { return mint((x * b.x) % mod); }
	mint operator/(mint b) { return *this * invert(b); }
    // mint operator+=(mint b) { return *this = *this + b; } // can be ignored if not necessary
    // mint operator-=(mint b) { return *this = *this - b; }
    // mint operator*=(mint b) { return *this = *this * b; }
    // mint operator/=(mint b) { return *this = *this / b; }
	mint invert(mint a) { // euclid for non prime mod
		return a ^ (mod - 2);
	}
	mint operator^(ll e) {
		if (!e) return mint(1);
		mint r = *this ^ (e / 2); r = r * r;
		return e&1 ? *this * r : r;
	}
};
