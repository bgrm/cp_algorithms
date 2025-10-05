namespace VerCover
{
    vector <int>* G;
    int* part;
    bool* res;
    void dfs(int v)
    {
        for (int u : G[v])
            if (part[u] != 0 and !res[u])
            {	res[u] = true;	dfs(part[u]);	}
    }
    void run(vector <int>* g, int n, int* Pin, bool* Rout)
    {
        G = g, part = Pin, res = Rout;
        FOR(i, 1, n+1)	if (part[i] == 0)	dfs(i);
        FOR(i, 1, n+1)
            if (part[i] != 0 and !res[part[i]])
                res[i] = true;
    }
};
