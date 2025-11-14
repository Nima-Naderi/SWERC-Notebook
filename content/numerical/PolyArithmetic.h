// tested on yosupo inv of formal power series

#pragma once
#include "NumberTheoreticTransform.h"

using poly = vector<Z>;

void fix(poly& a) {
    while (a.size() and a.back().x == 0) {
        a.pop_back();
    }
}

poly add(poly a, poly b) {
    int n = max(a.size(), b.size());
    poly res(n);
    for (int i = 0; i < (int)a.size(); i++) res[i] += a[i];
    for (int i = 0; i < (int)b.size(); i++) res[i] += b[i];
    return res;
}

poly sub(poly a, poly b) {
    int n = max(a.size(), b.size());
    poly res(n);
    for (int i = 0; i < (int)a.size(); i++) res[i] += a[i];
    for (int i = 0; i < (int)b.size(); i++) res[i] -= b[i];
    return res;
}

poly mult(poly a, poly b) {
    fix(a), fix(b);
    return conv(a, b); 
}

poly inv(poly& a, int m) {
    poly p(1), two(1);
    two[0] = 2;
    p[0] = Z(1) / a[0];
         
    int k = 1;
    while (k < m) {
        k *= 2;
        poly q(k);
        for (int i = 0; i < min((int)a.size(), k); i++) q[i] = a[i];
        p = mult(p, sub(two, mult(q,p)));
        //p = (p * (two - q * p));
        p.resize(k);
    }
    p.resize(m);
    return p;
}
