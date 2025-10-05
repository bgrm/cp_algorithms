namespace MatInt
{
	int n, parent[maxN];
	bool Y1[maxN], Y2[maxN], *S;
	pair <long long, int> dist[maxN];
	vector <int> G[maxN];
	long long *W;
	queue <int> Q;
	
	void build1();
	void build2();
	
	int aug()
	{
		FOR(i, 1, n+1)
			G[i].resize(Y1[i] = Y2[i] = false), dist[i] = {INF, 0};
		build1(), build2();
		#define RELAX(v, c, u)	dist[v] = c, parent[v] = u, Q.push(v)
		
		FOR(i, 1, n+1)	if (Y1[i])
			RELAX(i, make_pair(W[i], 0), 0);
				
		while (!Q.empty())
		{
			int v = Q.front(); Q.pop();
			for (int u : G[v])
			{
				pair <long long, int> prop = {dist[v].ft + W[u], dist[v].sd + 1};
				if (prop < dist[u])	RELAX(u, prop, v);
			}
		}
		int ret = 0;
		FOR(i, 1, n+1)
			if (Y2[i] and dist[i] < dist[ret])
				ret = i;
		return ret;
	}
	
	long long run(int nn, long long* win, bool* sout)
	{
		n = nn, W = win, S = sout;
		FOR(i, 1, n+1)
			W[i] = -W[i], S[i] = false;
		long long ret = 0;
		while (ret = aug())
			for (int v = ret; v != 0; v = parent[v])
				W[v] = -W[v], S[v] = !S[v];
		FOR(v, 1, n+1)
			S[v] ? ret += W[v] : W[v] = -W[v];
		return ret;
	}
};
