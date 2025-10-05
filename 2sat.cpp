struct S_2SAT
{
    int inCtr, sccCtr, low[maxN], in[maxN], scc[maxN], S[maxN], tp;
    vector <int> G[maxN];
    int dfs(int v)
    {
        low[v] = in[v] = ++inCtr;  S[tp++] = v;
        for (int u : G[v])	if (in[u] >= 0)
        	low[v] = min(low[v], in[u] == 0 ? dfs(u) : in[u]);
        if (in[v] != low[v])    return low[v];
        for (int u=-1; u!=v;)
        {
            u = S[--tp];
            scc[u] = sccCtr;
            in[u] *= -1;
        }
        sccCtr++;	return low[v];
    }
    int trans(int a)
    {	return a < 0 ? -2*a - 1 : 2*a - 2;	}
    void clear(int n)
    {
        FOR(i, 0, n)
            G[i].resize(0), low[i] = in[i] = scc[i] = 0;
        inCtr = sccCtr = 0;
    }
    bool comp(vector <pair <int, int> >& T, int n, bool* res)
    {
        n *= 2;
        for (auto [u, v] : T)
        {
        	u = trans(u), v = trans(v);
        	G[u^1].pb(v); G[v^1].pb(u);
        }
        FOR(i, 0, n)	if (in[i] == 0)   dfs(i);
        int *neg = low, *sccState = in;
        for (int i=0; i<n; i+=2)
        {
            int a = scc[i], b = scc[i+1];
            neg[a] = b, neg[b] = a;
            if (a == b) {	clear(n); return false;	}
        }
        FOR(i, 0, sccCtr)
            if (sccState[i] < 0)
                sccState[i] = 1, sccState[neg[i]] = 0;
        for (int i=0; i<n; i+=2)
            res[i/2+1] = sccState[scc[i]] == 1;
        clear(n); return true;
    }
};