struct LiChao
{
	Fun F[MEM];
	int S[MEM][2], n;
	long long P, Q;
	bool maxi;
	
	long long val(Fun& f, long long x) {	return f.ft * x + f.sd;	}

	bool domInf(Fun& f, Fun& g)	{	return f.ft > g.ft;	}

	void add(Fun f)
	{
		if (!maxi) f = {-f.ft, -f.sd};	//	f -> -f
		long long v = 1, p[2] = {P, Q};
		while (true)
		{
			if (v > n)
			{	F[++n] = f;	break;	}
			long long r = (p[0] + p[1]) / 2;
			Fun& g = F[v];
			if (val(f, r) > val(g, r))	swap(f, g);
			if (p[0] == r)	break;
			bool s = domInf(g, f);
			p[s] = r;
			int& u = S[v][!s];
			if (u == 0)	u = n+1;
			v = u;
		}
	}
	void init(long long p, long long q, bool _maxi = true, const vector <Fun>& T = {})
	{
		FOR(i, 0, n+1) S[i][0] = S[i][1] = 0;
		n = 0, P = p, Q = q, maxi = _maxi;
		for (Fun f : T)	add(f);
	}
	long long query(long long x)
	{
		long long v = 1, ret = -INF, p[2] = {P, Q};
		while (v != 0)
		{
			remax(ret, val(F[v], x));
			long long r = (p[0] + p[1]) / 2;
			p[x < r] = r;
			v = S[v][x >= r];
		}
		return maxi ? ret : -ret;
	}
}alg;
