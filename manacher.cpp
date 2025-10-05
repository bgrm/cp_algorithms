struct Machenar
{   void countR(char* T, int* r, int n, int parity)
    {
        int p = 0;
        FOR(i, 1, n+1)
        {
            if (p + r[p] < i)	p = i;
            r[i] = min(r[p*2 - i], p + r[p] - i);
            while (T[i - r[i] - parity] == T[i + r[i] + 1])	 r[i]++;
            if (p + r[p] < i + r[i])	p = i;
        }
    }
    void machenar(char* T, int* r0, int* r1, int n)	
    {
        char a = T[0], b = T[n + 1];
        T[0] = '@', T[n + 1] = '#';	
        countR(T, r0, n, 0);	countR(T, r1, n, 1);
        T[0] = a, T[n + 1] = b;
    }
};
