typedef vector <long long> Pol;
{
	void polyDiv(const Pol& A, const Pol& B, Pol& Q, Pol& R)
	{
		int n = SZ(A) - 1, m = SZ(B) - 1;
		
		if (n < m)
		{	Q = {0}; R = A; return;	}
		static Pol P;	P.assign(n+1, 0);
		Q.resize(n-m+1);
		long long b = qpow(B[m], mod-2);
		
		FORD(i, n-m, -1)
		{
			Q[i] = (A[i+m] - P[i+m] + mod) % mod;
			multMod(Q[i], b);
			FOR(j, 0, m+1)
				addMod(P[i+j], Q[i] * B[j]);
		}
		R.resize(m);
		FOR(i, 0, m)
			R[i] = (A[i] - P[i] + mod) % mod;
		if (R.empty())		R.pb(0);
		while (SZ(R) > 1 and R.back() == 0)
			R.pop_back();
	}
	void mult(Pol& A, const Pol& B)
	{
		int n = SZ(A)-1, m = SZ(B)-1;
		static Pol C;	C.assign(n+m+1, 0);
		FOR(i, 0, n+1) FOR(j, 0, m+1)
			addMod(C[i+j], A[i] * B[j]);
		A = C;
	}
	void modul(Pol& A, const Pol& B)
	{
		static Pol temp[2];
		polyDiv(A, B, temp[0], temp[1]);
		A = temp[1];		
	}
	Pol qpow(long long m, const Pol& A)
	{
		Pol ret{1}, p{0, 1};	modul(ret, A);
		for (; m; m /= 2)
		{
			if (m & 1ll)	mult(ret, p), modul(ret, A);
			mult(p, p), modul(p, A);
		}
		return ret;
	}
	void euc(Pol& A, Pol& B, Pol& G)
	{
		if (B.back() == 0)
		{	G = A;	return;	}
		modul(A, B);
		euc(B, A, G);
	}
}
