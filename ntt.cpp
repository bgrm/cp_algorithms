namespace NTT
{
    long long A[maxN];
	vector <long long> R[30];
    unsigned int bitrev[maxN];
    void init()
    {
    	FOR(i, 0, maxN)
			bitrev[i] = bitrev[i>>1]>>1 | (i&1)<<31;
    	long long r = 3, s;
		while ((s = qpow(r, RNG/2)) == 1 or s * s % mod != 1)
			r++;
		FOR(i, 0, LOG)
			R[i].pb(1);
		long long rpow = 1;
		FOR(i, 1, RNG+1)
		{
			multMod(rpow, r);
			int lg = LSB(i);
			FOR(j, 0, lg+1)
				R[j].pb(rpow);
		}
    }
    void ntt(long long* a, int n, int dir)
    {
        int w = __builtin_clz(n) + 1;
        FOR(i, 0, n)
		{
			int j = bitrev[i] >> w;
			if (i < j)
				swap(a[i], a[j]);
		}
        for (int len=2, lg=1; len<=n; len*=2, lg++)
        {
			vector <long long>& rpow = R[LOG - lg];
            for (long long* t = a; t != a + n; t += len)
            {
                int j = dir == 1 ? 0 : SZ(rpow) - 1;
                FOR(i, 0, len/2)
                {
                    long long x = t[len/2 + i] * rpow[j];
                    t[len/2 + i] = (t[i] - x) % mod;
                    addMod(t[i], x);
					j += dir;
                }
            }
        }
		long long u = dir == 1 ? 1 : qpow(n, mod-2);
		FOR(i, 0, n)
		{
			a[i] %= mod;
			a[i] = (a[i] + mod) * u % mod;
		}
    }
	typedef vector <long long> POL;
    void mult(const POL& x, const POL& y, POL& z)
    {
        int g = 1, n = SZ(x), m = SZ(y), k = n + m - 1;
        while (g < k)   g *= 2;
        FOR(i, 0, g)	A[i] = i < n ? x[i] : 0;
		ntt(A, g, 1);
		z.resize(g);
		FOR(i, 0, g)	z[i] = i < m ? y[i] : 0;
		ntt(&z[0], g, 1);
        FOR(i, 0, g) multMod(z[i], A[i]);
		ntt(&z[0], g, -1);
		z.resize(k);
    }
}
