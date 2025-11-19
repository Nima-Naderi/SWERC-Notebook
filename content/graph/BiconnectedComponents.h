/**
 * Author: Jiakai Hu
 * Date: 2025-11-19
 * Description: finds biconnected components (connected after vertex removal)
 */
#pragma once

const int N = 5e5 + 1;

bitset<N> arti; 
vector<int> g[N], st, comp[N]; 
int n, ptr, ncc, in[N], low[N], id[N];

void dfs(int u, int from = -1) {
    in[u] = low[u] = ++ptr;
    st.emplace_back(u);
    for (int v : g[u]) if (v ^ from) {
        if (!in[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= in[u]) {
                arti[u] = ~from or in[v] > in[u] + 1;
                comp[++ncc].emplace_back(u);
                while (comp[ncc].back() ^ v) {
                    comp[ncc].emplace_back(st.back());
                    st.pop_back();
                }
            } 
        } 
		else low[u] = min(low[u], in[v]);
    }
}

void bcc() {
    for (int i = 0; i < n; i++) {
        if (!in[i]) {
            dfs(i);
            if (g[i].empty()) comp[++ncc].push_back(i); // COMPS NUMBERED 1..ncc INCLUDED
        }
    }
}

// BLOCK CUT TREE
// vector<int>  tree[N]; 
// void buildTree() {
//     ptr = 0;
//     for (int i = 0; i < n; ++i) { // index nodes properly here
//         if (arti[i]) id[i] = ++ptr;
//     }
//     for (int i = 1; i <= ncc; ++i) {
//         int x = ++ptr;
//         for (int u : comp[i]) {
//             if (arti[u]) tree[x].emplace_back(id[u]), tree[id[u]].emplace_back(x);
//             else id[u] = x;
//         }
//     }
// }

