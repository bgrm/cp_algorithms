struct BCC
{ 
	vector <int>* G;
	pair <int, int>* E;
	int in[maxN], low[maxN], *BC, bCtr;
	stack <int> S;
	void dfs(int v, int fet)
	{
		static int inCtr = 0;
		in[v] = low[v] = ++inCtr;
		for (int e : G[v]) if (e != fet)
		{
			int u = oth(e, v);
				
			if (in[u] != 0)
			{
				if (in[u] < in[v])
					S.push(e);
				remin(low[v], in[u]);
			}			
			else
			{
				S.push(e);
				dfs(u, e);
				remin(low[v], low[u]);
				if (low[u] >= in[v])
				{
					bCtr++;
					for (int f=-1; f!=e; S.pop())
						BC[f = S.top()] = bCtr;
				}	
			}
		}
	}
	int run(int n, vector <int>* g, pair <int, int>* e, int* out)
	{
		G = g;	E = e;	BC = out;
		fill(in, in+n+1, 0);
		bCtr = 0;
		FOR(i, 1, n+1) if (in[i] == 0)
			dfs(i, -1);
		return bCtr;
	}
};

