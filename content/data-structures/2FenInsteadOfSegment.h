/**
 * Author: Nima Naderi Ghotbodini
 * Date: 2024-11-28
 * Source: CodeForces blogs
 * Description: Does advanced queries with two fenwicks
 * Time: $O(\log N)$.
 * Status: Tested on codeforces
 */
#pragma once

ll Fen[2][MXN];
void Add(int id, int p, int x){
    for(; p < MXN; p += p & -p) Fen[id][p] += x;
}
ll Ask(int id, int p){
    ll niw = 0;
    for(; p; p -= p & -p) niw += Fen[id][p];
    return niw;
}
void UpdFen(int l, int r, int x){
    Add(0, l, x);
    Add(0, r + 1, -x);
    Add(1, l, x * (l - 1));
    Add(1, r + 1, -x * r);
}
ll Get(int r){
    return Ask(0, r) * r - Ask(1, r);
}
ll GetFen(int l, int r){
    return Get(r) - Get(l - 1);
}

