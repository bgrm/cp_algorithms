struct UnionSepOffline
{
	int F[maxN], sz[maxN], t, offset, qbegin, qend;
	bool* res;
	map <PII, int> birth;	
	pair <PII, int> Q[maxT];
	vector <PII> tree[maxTs];
	#define UNFOLD(p, a, b)	int a = find(p.first), b = find(p.second)
	int find(int a)
	{	while (F[a] != a)	a = F[a];	return a;	}
	void onion(PII& p)
	{
		UNFOLD(p, a, b);
		if (sz[a] < sz[b])	swap(a, b);
		if (a != b)			F[b] = a, sz[a] += sz[b];
		p = {a, b};
	}
	void add(int v, int left, int right)
	{
		if (left >= qend or right <= qbegin) return;
		if (left >= qbegin and right <= qend)
		{
			tree[v].pb(Q[qbegin - offset].first);
			return;
		}
		add(v * 2, left, (left + right) / 2);
		add(v*2+1, (left + right) / 2, right);
	}
	void dfs(int v)
	{
		for (auto& p : tree[v])	onion(p);
		if (v < offset) dfs(v * 2), dfs(v*2+1);
		else
		{
			int i = v - offset;
			if (Q[i].second == 0)
			{
				UNFOLD(Q[i].first, a, b);
				res[i] = a == b;
			}
		}
		for (int i=tree[v].size()-1; i>=0; i--)
		{
			int a,b; tie(a,b) = tree[v][i];
			if (a != b)		F[b] = b, sz[a] -= sz[b];
		}
	}
	void symulate(int n, bool* Rout)
	{
		res = Rout;
		for (offset = 1; offset < t; offset *= 2);
		FOR(i, 1, n+1)	F[i] = i, sz[i] = 1;
		FOR(i, 0, t)	if (Q[i].second != 0)
		{
			qbegin = i + offset;
			qend = Q[i].second + offset;
			add(1, offset, offset*2);
		}
		dfs(1);
	}
	bool dodaj(int a, int b)
	{
		if (b < a)	swap(a, b);
		auto it = birth.find({a, b});
		if (it != birth.end() and it->second != -1)	return false;
		Q[t].first = {a, b};
		birth[{a, b}] = t++;
		return true;	
	}
	void zabij(int a, int b)
	{
		if (b < a)	swap(a, b);
		int start = birth[{a, b}];
		if (start == -1)	return;
		Q[start].second = t;
		birth[{a, b}] = -1;
	}
	void query(int a, int b)
	{	Q[t++].first = {a, b};	}
	void clean()
	{
		FOR(i, 1, offset*2)	tree[i].clear();
		FOR(i, 0, t)		Q[i].second = 0;
		t = 0;	birth.clear();
	}
}alg;
