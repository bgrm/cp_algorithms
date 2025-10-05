struct Max_flow
{
	vector <int> *G;
	int source, target, bfsctr, parent[maxN], vis[maxN], Q[maxN];
    long long* cap[maxN];
	bool bfs()
	{
		vis[source] = ++bfsctr;	Q[0] = source;
		for (int qF=0, qB=1; qF != qB; qF++)
		{
			int v = Q[qF];
			for (int u : G[v])
			{
				if (vis[u] == bfsctr or cap[v][u] <= 0)	continue;
				vis[u] = bfsctr; parent[u] = v;
				Q[qB++] = u;
				if (u == target)
				{	qF = qB - 1;	break;	}
			}
		}
		return vis[target] == bfsctr;		
	}
	long long maxflow(vector <int>* Gin, long long Cin[maxN][maxN],
				int n, int src, int trg)
	{
		G = Gin; source = src; target = trg;
        FOR(i, 0, n+1)    cap[i] = Cin[i];
		long long res = 0;
		while (bfs())
		{
			long long mc = INF;
			for (int v = target; v != source; v = parent[v])
				mc = min(mc, cap[parent[v]][v]);
			for (int v = target; v != source; v = parent[v])
				cap[parent[v]][v] -= mc, cap[v][parent[v]] += mc;
			res += mc;
		}
		return res;
	}
};
