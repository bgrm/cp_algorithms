namespace FFT
{
	using _T = double;
	#define CMPX complex <_T>
    CMPX A[maxN], B[maxN], C[maxN], D[maxN];
	vector <CMPX> omega[30];
    unsigned int bitrev[maxN];
    void init()
    {
    	FOR(i, 0, maxN)
			bitrev[i] = bitrev[i>>1]>>1 | (i&1)<<31;
		_T ang = M_PI / (maxN / 2);
		FOR(i, 0, LOG)
			omega[i].pb(CMPX(1, 0));
    	FOR(i, 1, maxN+1)
		{
			CMPX om(cos(ang * i), sin(ang * i));
			int lg = LSB(i);
			FOR(j, 0, lg+1)
				omega[j].pb(om);
		}
    }
    void fft(CMPX* a, int n, int dir)
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
			vector <CMPX>& om = omega[LOG - lg];
            for (CMPX* t = a; t != a + n; t += len)
            {
                int j = dir == 1 ? 0 : SZ(om) - 1;
                FOR(i, 0, len/2)
                {
                    CMPX x = t[len/2 + i] * om[j];
                    t[len/2 + i] = t[i] - x;
                    t[i] += x;
					j += dir;
                }
            }
        }
		a[n] = a[0];
    }
	#define L(t, i) (t[i] + conj(t[g-i]))
	#define R(t, i) (t[i] - conj(t[g-i]))
	#define CAST(x) llround((x) / g)   

	template <typename TT> void mult(vector <TT>& x, vector <TT>& y, vector <TT>& z)
    {
        int g = 1, n = SZ(x), m = SZ(y); z.resize(n+m-1);
        while (g < SZ(z))   g *= 2;
        FOR(i, 0, g)
        	A[i] = CMPX(i < n ? x[i] : 0, 0);
        fft(A, g, 1);
        FOR(i, 0, g)
        	B[i] = CMPX(i < m ? y[i] : 0, 0);
        fft(B, g, 1);
        FOR(i, 0, g)
        	B[i] *= A[i];
        fft(B, g, -1);
        FOR(i, 0, SZ(z))	z[i] = CAST(B[i].real());
    }
	template <typename TT> void multQ(vector <TT>& x, vector <TT>& y, vector <TT>& z)
    {
        int g = 1, n = SZ(x), m = SZ(y); z.resize(n+m-1);
        while (g < SZ(z))   g *= 2;
        FOR(i, 0, g)
			A[i] = {i < n ? x[i] : 0, i < m ? y[i] : 0};
		fft(A, g, 1);
		FOR(i, 0, g)
			B[i] = L(A, i) * R(A, i) * CMPX(0, -0.25);
		fft(B, g, -1);
		FOR(i, 0, SZ(z))
			z[i] = CAST(B[i].real());
    }
	template <typename TT> void multA(vector <TT>& x, vector <TT>& y, vector <TT>& z)
    {
        int g = 1, M = 1 << 15, sz = SZ(x) + SZ(y) - 1;
        while (g < sz)   g *= 2;
        #define INIT(t, w) FOR(i, 0, g) w[i] = i < SZ(t) ? CMPX(t[i] % M, t[i] / M) : 0
		INIT(x, C);	fft(C, g, 1);
		INIT(y, D);	fft(D, g, 1);
		FOR(i, 0, g)
		{
			A[i] = L(C, i) * L(D, i) * CMPX(0.25, 0) - R(C, i) * R(D, i) * CMPX(0, 0.25);
			B[i] = (L(C, i) * R(D, i) + R(C, i) * L(D, i)) * CMPX(0, -0.25);
		}
		fft(A, g, -1);
		fft(B, g, -1);
		z.resize(sz);
		FOR(i, 0, sz)
		{
			long long a = CAST(A[i].real()) % mod, b = CAST(B[i].real()) % mod, c = CAST(A[i].imag()) % mod; 
			z[i] = (a + b * M + c * M * M) % mod;
		}
    }
}
