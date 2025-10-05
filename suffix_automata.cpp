struct SuffixAut
{
	int link[maxN], len[maxN], trans[maxN][Alph], num, last;
	void init()
	{
		FOR(i, 0, Alph) trans[0][i] = trans[maxN-1][i] = -1;
		link[maxN-1] = last = 0;
		link[0] = -1;
		num = 1;
	}
	void cp(int a, int b)
	{
		copy(trans[b], trans[b] + Alph, trans[a]);	link[a] = link[b];
	}
	void add(char cc)
	{
		int p = last, c = cc-'a';
		cp(num, maxN-1);
		len[num] = len[last] + 1;
		last = num++;
		while (p != -1 and trans[p][c] == -1)
			trans[p][c] = last, p = link[p];
		if (p == -1)
			return;
		int q = trans[p][c];
		if (len[q] == len[p] + 1)
		{
			link[last] = q;
			return;
		}
		int clone = num++;
		cp(clone, q);
		len[clone] = len[p] + 1;
		link[q] = link[last] = clone;
		while (p != -1 and trans[p][c] == q)
			trans[p][c] = clone, p = link[p];
	}
	int jp[maxL][maxN], card[maxN], sufState[maxN];
	vector <int> G[maxN];
	bool terminal[maxN];
	void clear()
	{
		FOR(i, 0, num)
		{
			card[i] = sufState[i] = terminal[i] = 0;
			G[i].resize(0);
		}	
	}
	void dfs(int v)
	{
		for (int u : G[v])
			dfs(u),	card[v] += card[u];
	}
	void bonus(int n)
	{
		FOR(i, 1, num)
		{
			G[link[i]].pb(i);
			jp[0][i] = link[i];
		}
		jp[0][0] = 0;
		FOR(lg, 1, maxL) FOR(i, 0, num)
			jp[lg][i] = jp[lg-1][jp[lg-1][i]];
		int v = 0;
		FOR(i, 0, n)
		{
			v = trans[v][S[i] - 'a'];
			sufState[i] = v;
			card[v] = 1;
		}
		dfs(0);
		card[0] = 0;
		for (; v != -1; v = link[v])
			terminal[v] = true;
	}
	int getState(int a, int b)
	{
		int c = b - a + 1;
		int v = sufState[b];
		for (int i=maxL-1; i>=0; i--)
			if (len[jp[i][v]] >= c)
				v = jp[i][v];
		return v;
	}
};
