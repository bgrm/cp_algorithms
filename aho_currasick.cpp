struct Aho
{
	int n, T[maxN][Alph], F[maxN], N[maxN], o[maxN];
	queue <int> Q;
	void add(char* t, int m, int ind)
	{
		int v = 1;
		FOR(i, 0, m)
		{
			int& u = T[v][t[i] - 'a'];
			if (u == 0)	u = ++n;
			v = u;
		}
		o[v] = ind + 1;	
	}
	void calcF()
	{
		F[1] = 1;
		FOR(c, 0, Alph)
		{
			int& u = T[1][c];
			if (u == 0)	u = 1;
			else 		F[u] = 1, Q.push(u);
		}
		while (!Q.empty())
		{
			int v = Q.front();	Q.pop();
			FOR(c, 0, Alph)
			{
				int &u = T[v][c], w = F[v];
				if (u == 0)
				{
					u = T[w][c];
					continue;
				}
				F[u] = T[w][c];
				N[u] = o[F[u]] == 0 ? N[F[u]] : F[u];
				Q.push(u);
			}
		}
	}
	void query(char* t, int m, vector <pair <int, int> >* res)
	{
		int v = 1;
		FOR(i, 0, m)
		{
			v = T[v][t[i] - 'a'];
			int u = o[v] == 0 ? N[v] : v;
			for (; u != 0; u = N[u])	res.pb({i, o[u]-1});
		}
	}
	void clean()
	{
		FOR(i, 1, n+1)
		{
			FOR(c, 0, Alph)	T[i][c] = 0;
			F[i] = N[i] = o[i] = 0;
		}
		n = 1;
	}
};
	
