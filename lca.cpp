struct LCA
{
    pair <int, int> res, INF, T[maxTS];
    int offset, qbegin, qend, ctr, in[maxN], out[maxN];
    vector <int>* G;
    void min_priv(int v, int a, int b)
    {
        if (a >= qend or b <= qbegin)
            return;
        if (a >= qbegin and b <= qend)
        {	res = min(res, T[v]);	return;		}
        min_priv(v * 2, a, (a+b) / 2);
        min_priv(v*2+1, (a+b) / 2, b);
    }
    void dfs(int v, int h, int father)
    {
        in[v] = ctr;
        T[ctr++] = {h, v};
        for (int u : G[v]) if (u != father)
			dfs(u, h+1, v), T[ctr++] = {h, v};
        out[v] = ctr;
    }
    void init(vector <int>* g, int n, int root)
    {
        for (offset = 1; offset < n*2 - 1; offset *= 2);
        G = g; ctr = offset; INF = {n, n};
        dfs(root, 0, -1);
        FOR(i, ctr, offset*2)			T[i] = INF;
        for (int i=offset-1; i>0; i--)  T[i] = min(T[i * 2], T[i*2+1]);
    }
    int lca(int u, int v)
    {
        res = INF;
        qbegin = min(in[u], in[v]);
        qend = max(out[u], out[v]);
        min_priv(1, offset, offset * 2);
        return res.second;
    }
    int ver_heigth(int v)
    {   return T[in[v]].first;  }
    bool is_anc(int anc, int v)
    {	return in[anc] <= in[v] and out[v] <= out[anc];	}
};
