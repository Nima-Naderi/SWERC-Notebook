// does dfs to find bridges, then removes them and does dfs to find 2CCs

struct LowLink{
    int n, pos = 0;
    vi ord, low, par, blg;
    vector<vi> G, C;

    LowLink(vector<vi>& adj) : n(sz(adj)), ord(n,-1), low(n), par(n,-1), blg(n,-1), G(adj) {}

    bool bridge(int u,int v){
        if(ord[u] > ord[v]) swap(u,v);
        return ord[u] < low[v];
    }

    void dfs(int v){
        ord[v] = low[v] = pos++;
        int cnt = 0;
        for(int u : G[v]){
            if(u == par[v] && cnt == 0) cnt++;
            else if(~ord[u]) low[v] = min(low[v], ord[u]);
            else {
                par[u] = v;
                dfs(u);
                low[v] = min(low[v], low[u]);
            }
        }
    }

    void fill_comp(int v){
        C[blg[v]].emplace_back(v);
        for (int u : G[v]) {
            if (~blg[u] || bridge(u,v)) continue;
            blg[u] = blg[v];
            fill_comp(u);
        }
    }

    void add_comp(int v,int &k){
        if(~blg[v]) return;
        blg[v] = k++;
        C.emplace_back();
        fill_comp(v);
    }

    int build(){
        for(int i=0;i<n;i++) if(ord[i] < 0) dfs(i);

        int k = 0;
        for(int i=0;i<n;i++) add_comp(i, k);
        return k;
    }
};
