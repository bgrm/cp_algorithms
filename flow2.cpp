struct Max_flow_relabel_to_front
{
    long long ex[maxN];
    int H[maxN], nbr[maxN];
    list <int> L;
    long long maxflow (vector <int>* G, long long cap[][maxN], int n, int src, int trg)
    {
    	FOR(i, 1, n+1)	ex[i] = H[i] = nbr[i] = 0;
        L.clear();
        H[src] = n;
        for (int u : G[src])
        {
            ex[u] = cap[u][src] = cap[src][u];
            ex[src] -= cap[src][u];
            cap[src][u] = 0;
        }
        FOR(v, 1, n+1)	if (v != src and v != trg)	L.pb(v);
        for (auto it = L.begin(); it != L.end(); it++)
        {
            int v = *it, oldH = H[v];
            while (ex[v] > 0)
            {
                if (nbr[v] == G[v].size())
                {
                    H[v] = n * 2;
                    for (int w : G[v])	if (cap[v][w] > 0)
						H[v] = min(H[v], H[w]);
                    H[v]++;	nbr[v] = 0;	continue;
                }
                int u = G[v][nbr[v]];
                if (cap[v][u] > 0 and H[u] < H[v])
                {
                    long long d = min(ex[v], cap[v][u]);
                    ex[v] -= d; cap[v][u] -= d;
                    ex[u] += d; cap[u][v] += d;
                }
                else nbr[v]++;
            }
            if (oldH < H[v])
                L.erase(it), L.push_front(v), it = L.begin();
        }
        long long res = 0;
        for (int u : G[src])	res += cap[u][src];
        return res;
    }
};
