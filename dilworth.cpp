namespace DILW
{
	vector <int> G[maxN];
	int part[maxN];
	bool cover[maxN];
	
	vector <int> run(vector <int>* gin, int n, int* parent)
	{
		fill(parent, parent+n*2+1, 0);
		FOR(i, 1, n+1) for (int j : gin[i])
			G[n + i].pb(j), G[j].pb(n + i);
		Matching::run(G, n, n, part);
		VerCover::run(G, n, part, cover);
		vector <int> ret;
		FOR(i, 1, n+1)
		{
			if (!cover[i] and !cover[n + i])
				ret.pb(i);
			if (part[i] != 0)
				parent[i] = part[i] - n;
			cover[i] = cover[n + i] = part[i] = part[n + i] = 0;
			G[i].resize(0), G[n + i].resize(0);
		}
		return ret;
	}
}
