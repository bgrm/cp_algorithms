namespace HPI
{
	pair <Point, Point>* P;
	Point v[maxN];
	long long A[maxN], B[maxN], C[maxN];
	int inds[maxN];
	#define Ihalf(w) (w.x < 0 or (w.x == 0 and w.y > 0))
	
	bool inHp(int i, const Point& a)
	{		return v[i] % (a - P[i].first) > 0;	}
	
	bool cmp(int i, int j)
	{
		if (Ihalf(v[i]) xor Ihalf(v[j]))
			return Ihalf(v[i]);
		long long ilo = v[i] % v[j];
		return ilo == 0 ? inHp(j, P[i].first) : ilo > 0;
	}	
	void cross(int i, int j, long long& x, long long& y, long long& z)
	{
		x = B[i] * C[j] - B[j] * C[i];
		y = C[i] * A[j] - C[j] * A[i];
		z = A[i] * B[j] - A[j] * B[i];
	}
	bool crossInHp(int i, int j, int k, bool border = false)
	{
		long long x, y, z;
		cross(j, k, x, y, z);
		if (z < 0)	x = -x, y = -y, z = -z;
		long long a = z * (P[i].first % v[i]);
		long long b = Point(x, y) % v[i];
		return border ? a >= b : a > b;
	}
	int jazda(pair <Point, Point>* Pin, int n, vector <int>& res)
	{
		P = Pin;
		FOR(i, 0, n)
		{
			inds[i] = i;
			v[i] = P[i].second - P[i].first;
			A[i] = v[i].y;	B[i] = -v[i].x;
			C[i] = v[i] % P[i].first;
		}
		sort(inds, inds + n, cmp);
		res.pb(inds[0]);
		int s = 0;
		FOR(j, 1, n)
		{
			#define ASparl(a, b)	{	if (!inHp(a, P[b].first))	return 2;	}
			#define ASempty			{	if (!crossInHp(i, L, LL))	return 2;	}
			#define GET(a)			{	res.pb(a);	continue;	}	
			#define ASerase(d)		{	if (crossInHp(L, LL, i, true)) \
							{	d ? res.pop_back(),0 : s++; j--; continue;	}	}
			int i = inds[j], L = res.back();
			long long ilo = v[i] % v[L];
	
			if (ilo > 0)	return 1;
			if (ilo == 0)
			{
				if (Ihalf(v[i]) xor Ihalf(v[L]))
					return inHp(i, P[L].first) ? 1 : 2;
				else continue;
			}	
			if (res.size() - s == 1)	GET(i);	
			int LL = res[res.size() - 2];	
			ilo = v[i] % v[LL];
			
			if (ilo > 0)	ASempty;
			if (ilo == 0)	ASparl(i, LL);
			if (ilo < 0)	ASerase(1);
			
			L = res[s], LL = res[s+1];
			ilo = v[i] % v[L];
			
			if (ilo == 0)	ASparl(i, L);
			if (ilo <= 0)	GET(i);
			
			ilo = v[i] % v[LL];
			
			if (ilo < 0)	ASempty;
			if (ilo == 0)	ASparl(i, LL);
			if (ilo > 0)	ASerase(0);

			LL = res.back();			
			if (v[LL] % v[L] <= 0 or !crossInHp(i, LL, L, true))
				res.pb(i);
		}
		if (res.size()-s < 3 or v[res.back()] % v[res[s]] <= 0)
			return 1;
		res.erase(res.begin(), res.begin() + s);
		return 0;
	}
	vector <PointR> getPoints(vector <int>& is)
	{
		int n = is.size();
		vector <PointR> res(n);
		FOR(i, 0, n)
		{
			long long x, y, z;
			cross(is[i], is[(i+1)%n], x, y, z);
			res[i] = PointR(1.0*x/z, 1.0*y/z);
		}
		return res;
	}
}
