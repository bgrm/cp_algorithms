namespace MCMF
{
	struct Edge
	{
		int a, b;
		long long cap, lim, cst;
		
		Edge(int u=0, int v=0, long long cp=0, long long cs=0)
		:	a(u), b(v), cap(cp), lim(cp), cst(cs)	{}
		
		bool valid(int trg)
		{	return trg == b ? cap != 0 : cap != lim;	}
		
		void push(int trg, long long dv)
		{	cap += trg == b ? -dv : dv;	}
		
		int oth(int v)
		{	return a ^ b ^ v;	}
		
		long long capacity(int trg)
		{	return trg == b ? cap : lim - cap;	}
		
		long long cost(int trg)
		{	return trg == b ? cst : -cst;	}
	}E[maxM];
			
	priority_queue <pair <long long, int> > H;
	queue <pair <long long, int> > Q;
	Edge* pe[maxN];
	long long dist[maxN], pot[maxN], m;
	vector <Edge*> G[maxN];
	
	void addEdge(int a, int b, long long cp, long long cs)
	{
		if (a == b)	return;
		G[a].pb(E+m);
		G[b].pb(E+m);
		E[m++] = Edge(a, b, cp, cs);
	}
	void seekPaths(int s, int n, auto& H)
	{
		fill(dist, dist+n+1, INF);
		#define UPDT(v, c, p) dist[v] = c, pe[v] = p, H.push({-c, v})
		UPDT(s, 0, 0);
		while (!H.empty())
		{
			long long d, v; tie(d, v) = H.top();
			H.pop();	if (-d != dist[v])	continue;
			for (Edge* e : G[v])
			{
				int u = e->oth(v);
				long long prop = dist[v] + e->cost(u) + pot[v] - pot[u];
				if (e->valid(u) and prop < dist[u])
					UPDT(u, prop, e);
			}
		}
	}
	pair <long long, long long> run(int src, int trg, int n)
	{
		seekPaths(src, n, Q);
		copy(dist, dist+n+1, pot);
		long long flow = 0, cost = 0;
		while (seekPaths(src, n, H), dist[trg] != INF)
		{
			FOR(v, 0, n+1)	pot[v] += dist[v];
			long long dx = INF;
			for (int v = trg; v != src; v = pe[v]->oth(v))
				remin(dx, pe[v]->capacity(v));
			for (int v = trg; v != src; v = pe[v]->oth(v))
				pe[v]->push(v, dx);
			flow += dx;
			cost += dx * pot[trg];
		}
		return {flow, cost};
	}
	void clear(int n)
	{	
		m = 0;	FOR(i, 0, n+1)	G[i].resize(pot[i] = 0);
	}
}
