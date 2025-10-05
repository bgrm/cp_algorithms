struct HL_dec
{
	int *in, *R, *F, inctr, son[maxN];
	vector <int>* G;
	int dfs0(int v)
	{
		int sz = 1, maxsz = 0, x;	son[v] = -1;
		for (int u : G[v]) if (u != F[v])
		{
			F[u] = v;	sz += x = dfs0(u);
			if (maxsz < x)	maxsz = x, son[v] = u;
		}
		return sz;
	}
	void dfs(int v, int myroot)
	{
		in[v] = inctr++; 	R[v] = myroot;
		if (son[v] != -1)	dfs(son[v], myroot);
		for (int u : G[v])	if (u != F[v] and u != son[v])	dfs(u, u);
	}
	void f(vector<int>* Gin, int* inout, int* Rout, int* Fout, int rt=1)
	{
		G = Gin, in = inout, R = Rout, F = Fout;
		F[rt] = inctr = 0; in[0] = -1;
		dfs0(rt); dfs(rt, rt);
	}
	void query(int a, int b) // a ^ b
	{
		#define RT R[a]
		for (; in[a] >= in[b]; a = F[RT])
			tree.operation(max(in[b], in[RT]), in[a]);
	}
};
