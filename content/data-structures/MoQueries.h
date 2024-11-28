/**
 * Author: Nima Naderi Ghotbodini
 * Date: 2024-11-28
 * Source: https://codeforces.com/contest/1514/submission/113524329
 * Description: Answer interval or tree path queries by finding an approximate TSP through the queries,
 * and moving from one query to the next by adding/removing points at the ends.
 * If values are on tree edges, change \texttt{step} to add/remove the edge $(a, c)$ and remove the initial \texttt{add} call (but keep \texttt{in}).
 * Time: O(N \sqrt Q)
 * Status: Tested on Codeforces
 */
#pragma once

bool CMP(int x, int y){
    if(Ql[x] / SQR == Ql[y] / SQR) return (Qr[x] < Qr[y]);
    return (Ql[x] / SQR < Ql[y] / SQR);
}
bool CmP(int x, int y){
    if(Ql[x] / SQR == Ql[y] / SQR) return ((Ql[x] / SQR) % 2) ^ (Qr[x] < Qr[y]);
    return (Ql[x] / SQR < Ql[y] / SQR);
}
void Add(ll x){ x = A[x]; /* ... */ }
void Ers(ll x){ x = A[x]; /* ... */ }
int main(){
    for(int i = 1; i <= q; i ++) cin >> Ql[i] >> Qr[i], vec.push_back(i);
    sort(vec.begin(), vec.end(), CmP);
    ll Ml = 1, Mr = 0;
    for(auto id : vec){
        int l = Ql[id], r = Qr[id];
        while(Mr < r) Mr ++, Add(Mr);
        while(l < Ml) Ml --, Add(Ml);
        while(Mr > r) Ers(Mr), Mr --;
        while(Ml < l) Ers(Ml), Ml ++;
    }
    return 0;
}
