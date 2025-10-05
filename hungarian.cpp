struct Hungarian
{
	long long *C[maxN], pot[maxN * 2], mluz[maxN * 2];
	int *part, n, ctr, qtop, qback, vis[maxN * 2], vluz[maxN * 2], Q[maxN];
	#define LUZ(a, b)	(C[a][(b) - n] - pot[a] - pot[b])
	inline void aug(int x, int y)
	{	while (x != 0)	part[y] = x, swap(part[x], y), x = vluz[x];	}
	inline void ins(int v, int prev)
	{
		FOR(j, n+1, n*2+1)
		{
			long long luz = LUZ(v, j);
			if (mluz[j] > luz)
				mluz[j] = luz, vluz[j] = v;
		}
		vis[v] = vis[part[v]] = ctr;
		Q[qback++] = v;	vluz[v] = prev;
	}
	long long f(int nn, long long Cin[maxN][maxN], int* partOut)
	{
		n = nn; part = partOut;
		FOR(i, 0, n*2+1) vis[i] = part[i] = pot[i] = 0;
		FOR(i, 0, n+1)	 C[i] = Cin[i];
		for (ctr=1; ctr<=n; ctr++)
		{
			fill(mluz + n+1, mluz + n*2+1, INF);
			ins(ctr, qback = qtop = 0);
			while (true)
			{
				for (int i = Q[qtop]; qtop != qback; qtop++)
				{
					FOR(j, n+1, n*2+1)
					if (vis[j] != ctr and LUZ(i, j) == 0)
					{
						if (part[j] == 0) {aug(i, j); goto Break;}
						ins(part[j], i);
					}
				}
				long long mn = INF;
				FOR(j, n+1, n*2+1)
					if (vis[j] != ctr)	remin(mn, mluz[j]);
				FOR(i, 1, n+1)
					if (vis[i] == ctr)	pot[i] += mn;
				FOR(j, n+1, n*2+1)
					vis[j] == ctr	?	pot[j] -= mn : mluz[j] -= mn;
				FOR(j, n+1, n*2+1)
				if (vis[j] != ctr and mluz[j] == 0)
				{
					if (part[j] == 0)	{aug(vluz[j], j); goto Break;}
					ins(part[j], vluz[j]);
				}
			} Break: ;
		}
		long long cost = 0;
		FOR(i, 1, n+1)	cost += C[i][part[i] - n];
		return cost;
	}
}alg;
