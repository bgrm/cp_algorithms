struct Dominator_tree
{
    vector <int>* G;
    vector <int> Ginv[maxN], bucket[maxN]; 
    int inctr, in[maxN], ininv[maxN], sdom[maxN],
		idom[maxN], parent[maxN], anc[maxN], F[maxN];

    int find(int v, bool isRecroot = true)
    {
        if (anc[v] == v)    return (isRecroot ? v : 0);
        int u = find(anc[v], false);
        if (u == 0) return F[v];
        if (sdom[u] < sdom[F[v]])   F[v] = u;
        anc[v] = anc[anc[v]];
        return F[v];
    }
    void dfs(int v)
    {
        in[v] = ++inctr, ininv[inctr] = v;
        for (int u : G[v])
        {
            if (in[u] == 0)		dfs(u), parent[in[u]] = in[v];
            Ginv[in[u]].pb(in[v]);
        }
    }
    void clear(int n)
    {
        FOR(i, 1, inctr+1)
            Ginv[i].resize(0), bucket[i].resize(0);
        fill(idom, idom + inctr + 1, 0);
        fill(F, F + inctr + 1, 0);
        fill(in, in + n + 1, 0);	inctr = 0;
    }
    void genDomTree(vector <int>* g, int n, int s, vector <int>* res)
    {
        G = g;  dfs(s);
        FOR(i, 1, inctr+1)	anc[i] = sdom[i] = i;
        for (int i=inctr; i>1; i--)
        {
            for (int v : Ginv[i])
				remin(sdom[i], sdom[find(v)]);
            bucket[sdom[i]].pb(i);
            int fath = parent[i];
            anc[i] = fath, F[i] = i;
            for (int v : bucket[fath])
            {
                int u = find(v);
                idom[v] = (sdom[u] == sdom[v] ? fath : u);
            }
            bucket[fath].resize(0);
        }
        FOR(i, 2, inctr+1)
        {
            int& id = idom[i];
            if (id != sdom[i])  id = idom[id];
            res[ininv[id]].pb(ininv[i]);
        }
        clear(n);
    }
};
