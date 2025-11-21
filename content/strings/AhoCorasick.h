/**
 * Author: Nima Naderi Ghotbodini
 * Date: 2024-11-28
 * Source: https://codeforces.com/contest/163/submission/108176654
 * Description: Aho-Corasick automaton, used for multiple pattern matching.
 * Initialize with AhoCorasick ac(patterns); the automaton start node will be at index 0.
 * find(word) returns for each position the index of the longest word that ends there, or -1 if none.
 * findAll($-$, word) finds all words (up to $N \sqrt N$ many if no duplicate patterns)
 * that start at each position (shortest first).
 * Duplicate patterns are allowed; empty patterns are not.
 * To find the longest words that start at each position, reverse all input.
 * For large alphabets, split each symbol into chunks, with sentinel bits for symbol boundaries.
 * Time: construction takes $O(26N)$, where $N =$ sum of length of patterns.
 * find(x) is $O(N)$, where N = length of x. findAll is $O(NM)$.
 * Status: Tested on codeforces
 */
#pragma once

const ll SGM = 26;
int n, q, ts = 1, timer;
int Q[MXN], Ver[MXN], nxt[MXN][SGM], lps[MXN];
char s[MXN];
void Add(int id){
    scanf("%s", s); int sz = strlen(s);
    int u = 1;
    for(int h = 0; h < sz; h ++){
        if(!nxt[u][s[h] - 'a']) nxt[u][s[h] - 'a'] = ++ ts;
        u = nxt[u][s[h] - 'a'];
    }
    Ver[id] = u;
}
void Aho(){
    int L = 0, R = 0;
    for(int i = 0; i < SGM; i ++){
        if(!nxt[1][i]) nxt[1][i] = 1;
        else{
            Q[R ++] = nxt[1][i];
            lps[nxt[1][i]] = 1;
        }
    }
    while(L < R){
        int u = Q[L ++];
        adj[lps[u]].push_back(u); // Aho-tree
        for(int c = 0; c < SGM; c ++){
            if(!nxt[u][c]) nxt[u][c] = nxt[lps[u]][c];
            else{
                lps[nxt[u][c]] = nxt[lps[u]][c];
                Q[R ++] = nxt[u][c];
            }
        }
    }
}