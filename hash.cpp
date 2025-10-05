struct Hash
{
    long long H[maxN], pows[maxN], mod, p;
    void initialize (char* T, int n)
    {
        mod = 100000000000000099LL;
        p = 29, base = 8;
        pows[0] = 1; H[n] = 0;
        FOR(i, 1, n+1)
            pows[i] = pows[i - 1] * p % mod;
        for (int i=n-1; i>=0; i--)
            H[i] = (H[i + 1] * p + (T[i]-'a') + 1) % mod;
    }
    long long hash(int a, int b)
	{	b++; return myMod(H[a] - H[b] * pows[b-a]);	}
};
