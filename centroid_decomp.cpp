struct Centroid_Dec
{
	vector <int> *G, *C;
	bool taken[maxN];
	int *d, sz[maxN];
	int dfs(int v, int fat)
	{
		sz[v] = 1;
		for (int u : G[v])
			if (u != fat and !taken[u])
				sz[v] += dfs(u, v);
		return sz[v];
	}
	int f(int v, int depth)
	{
		int n = dfs(v, -1);
		bool moved = true;
		while (moved)
		{
			moved = false;
			for (int u : G[v])
				if (!taken[u] and n/2 < sz[u] and sz[u] < sz[v])
				{	v = u; moved = true; break;	}
		}
		d[v] = depth;
		taken[v] = true;
		for (int u : G[v])	if (!taken[u])
			C[v].pb(f(u, depth+1));
		return v;
	}
	int centDec(vector <int>* Gin, vector <int>* Cout, int* dout)
	{	G = Gin, C = Cout, d = dout;	return f(1, 0);		}
	void clear()	{	fill(taken, taken + maxN, false);	}
};
