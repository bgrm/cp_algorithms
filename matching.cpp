namespace Matching
{
    int *part, n, m, visctr, ser, dist[maxN], vis[maxN];
    int qb, Q[maxN];
    vector <int>* G;
	void ins(int v, int d)
	{
		dist[v] = d; vis[v] = visctr;
		if (d <= ser)	Q[qb++] = v;
	}	
    bool bfs()
    {
        visctr++;
        ser = n + m; qb = 0;
        FOR(i, 1, n+1) if (part[i] == 0) ins(i, 0);
        for (int qf = 0; qf != qb; qf++)
        {
            int v = Q[qf];
            for (int w : G[v])
            {
                int u = part[w];
                if (vis[u] == visctr)	continue;
                if (u == 0)
                {	ser = min(ser, dist[v]+1);	continue;	}
				ins(u, dist[v] + 2);
            }
        }
        visctr++;	return ser != n + m;
    }
    bool dfs(int v)
    {
        vis[v] = visctr;
        if (dist[v] > ser)	return false;
        for (int w : G[v])
        {
            int u = part[w];
            if (u == 0 or
            (vis[u] != visctr and dist[u] == dist[v] + 2 and dfs(u)))
            {	match(w, v); return true;	}
        }
        return false;
    }
    int run(vector <int>* Gin, int nn, int mm, int* partout)
    {
        G = Gin; n = nn; m = mm; part = partout;
        while (bfs())  FOR(i, 1, n+1)
			if (part[i] == 0) dfs(i);
        int res = 0;
        FOR(i, 1, n+1)	res += part[i] != 0;
        return res;
    }
};
