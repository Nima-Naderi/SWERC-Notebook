/**
 * Author: Nima Naderi
 * Date: 2025-11-21
 * Source: my brain
 * Description: nima
 * Time: O(n \log n)
 * Status: stress-tested
 */
#pragma once
const ll LOG = 22;
int n, pw; string s;
int rnk[MXN], SA[MXN], lcp[MXN], tmp[MXN], Cnt[MXN];
int rmq[LOG][MXN], lg[MXN];
inline void BuildSuffixArray(const string &s){
    assert((s[0] == '$') && (n + 1 == (int)s.size()));
    iota(SA + 1, SA + n + 1, 1), SA[0] = n + 1;
    for(int i = 1; i <= n; i ++) rnk[i] = s[i];
    int _Max = 'z', p = 1, k;
    for(pw = 0; p < n; pw ++){
        k = ((1LL << pw) >> 1), p = 1;
        for(int i = n - k + 1; i <= n; i ++){
            tmp[p ++] = i;
        }
        for(int i = 1; i <= n; i ++){
            if(SA[i] > k) tmp[p ++] = SA[i] - k;
        }
        for(int i = 0; i <= _Max; i ++) Cnt[i] = 0;
        for(int i = 1; i <= n; i ++) Cnt[rnk[i]] ++;
        for(int i = 1; i <= _Max; i ++){
            Cnt[i] += Cnt[i - 1];
        }
        for(int i = n; i; i --){
            SA[Cnt[rnk[tmp[i]]] --] = tmp[i];
        }
        swap(rnk, tmp);
        rnk[SA[1]] = p = 1;
        for(int i = 2; i <= n; i ++){
            if(tmp[SA[i - 1]] != tmp[SA[i]] || SA[i - 1] + k > n || tmp[SA[i - 1] + k] != tmp[SA[i] + k]){
                p ++;
            }
            rnk[SA[i]] = p;
        }
        _Max = p;
    }
    SA[0] = n + 1;
}
inline void BuildLcpTable(const string &s){
    assert((s[0] == '$') && (n + 1 == (int)s.size()));
    for(int i = 1, k = 0; i <= n; i ++){
        if(rnk[i] == n) continue;
        if(k) k --;
        while(s[i + k] == s[SA[rnk[i] + 1] + k]){
            k ++;
        }
        lcp[rnk[i] + 1] = k;
    }
}
int main(){
    cin >> s, n = (int)s.size(); s = "$" + s;
    BuildSuffixArray(s);
    BuildLcpTable(s);
    // BuildRmqLcp(); then ask LCP(i, r) like rmq
}
