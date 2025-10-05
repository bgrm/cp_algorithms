template <typename TT> struct RMQ
{
	TT T[maxL][maxN];
	#define F min

	void init(TT* t, int n)
	{
		copy(t, t+n, &T[0][0]);
		FOR(l, 1, maxL) FOR(i, 0, n+1 - (1<<l))
			T[l][i] = F(T[l-1][i], T[l-1][i + (1 << l-1)]);
	}
	TT query(int a, int b)
	{
		int l = MSB(b - a);
		return F(T[l][a], T[l][b - (1 << l)]);
	}
};