struct Convolution_xor
{
    void tf(int* a, int* res, int n)
    {
        copy(a, a + n, res);
        for (int len=1; len<n; len*=2)
            for (int* t=res; t!=res+n; t+=len*2)
                FOR(i, 0, len)
                {
                    int u = t[i];
                    subMod(t[i], t[len + i]);
                    addMod(t[len + i], u);
                }
    }
    void utf(int* a, int n)
    {
        for (int len=n/2; len>0; len/=2)
            for (int* t=a; t!=a+n; t+=len*2)
                FOR(i, 0, len)
                {
                    int u = t[len + i];
                    subMod (t[len + i], t[i]);
                    multMod(t[len + i], (mod+1)/2);
                    addMod (t[i], u);
                    multMod(t[i], (mod+1)/2);
                }
    }
    int temp[maxN];
    void convolution(int*a, int* b, int* c, int n)
    {
        tf(a, temp, n);	tf(b, c, n);
        FOR(i, 0, n)	multMod(c[i], temp[i]);
        utf(c, n);
    }
};
