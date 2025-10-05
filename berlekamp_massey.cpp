vector <long long> BM(const vector <long long>& T) 
{
    if (T.empty())	return {};
    long long n = SZ(T), L = 0, m = 0, b = 1;
    vector <long long> B(n, 0), C(n, 0), temp;
    B[0] = C[0] = 1;

    FOR(i, 0, n)
    {
    	m++;
        long long x = 0;
		FOR(j, 0, L+1)
            addMod(x, C[j] * T[i-j]);
        if (x == 0)	continue;

        temp = C;
        multMod(x, qpow(b, mod-2));
		FOR(j, m, n)
            addMod(C[j], mod - x * B[j-m] % mod);

        if (i < L*2)	continue;
		multMod(b, x);
        L = i + 1 - L, m = 0, B = temp;
    }
    C.resize(L + 1), C.erase(C.begin());
    for (long long &x : C)	multMod(x, mod-1);
    return C;
}
