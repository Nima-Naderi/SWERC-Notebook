/**
 * Author: kyooz
 * Date: 2025-11-19
 * Source: jiangly submissions
 * Inputs must be in [0, mod).
 * Time: O(N \log N) for more complex operations (high constant), O(N) for simple operations
 * Status: tested on yosupo inv, log, exp, pow
 */

using poly = vector<Z>;

void fix(poly &a) {
    while (a.size() and a.back().x == 0) a.pop_back();
}

poly trunc(poly a, int k) {
    poly f = a;
    f.resize(k);
    return f;
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

poly deriv(poly a) {
    if (a.empty()) return a;
    poly res(a.size() - 1);
    for (int i = 0; i < a.size() - 1; ++i) res[i] = a[i + 1] * (i+1);
    return res;
}

poly integr(poly a) {
    poly res(a.size() + 1);
    for (int i = 0; i < a.size(); ++i) res[i + 1] = a[i] / (i + 1);
    return res;
}

poly inv(poly a, int m) {
    poly x{Z(1)/a[0]};
    int k = 1;
    while (k < m) k *= 2, x = trunc(mult(x, (sub(poly{2}, mult(trunc(a, k), x)))), k);
    return trunc(x, m);
}

poly log(poly a, int m) {
    poly res = mult(deriv(a), inv(a, m));
    res = trunc(integr(res), m);
    return res;
}
    
poly exp(poly a, int m) {
    poly x{1};
    int k = 1;
    while (k < m) k *= 2, x = trunc(mult(x, add(sub(poly{1}, log(x, k)), trunc(a, k))), k);
    return trunc(x, m);
}
// for pow shift until first non zero coeff, then reshift back, p^x = exp(x * log p) 
