struct Gauss
{
    long double ABS(long double a)
    {   return a < 0 ? -a : a;  }
    int gauss(long double T[maxN][maxN], int n)
    {
        bool resUnique = true;
        FOR(d, 0, n)
        {
            long double val = T[d][d];
            int rtc = d;
            FOR(i, d+1, n)
                if (ABS(val) < ABS(T[i][d]))
                    val = T[i][d], rtc = i;

            if (val == 0)   continue;
            if (rtc != d)
                FOR(j, d, n+1)
                    swap(T[d][j], T[rtc][j]);

            FOR(i, 0, n)
            {
                if (i == d) continue;
                val = T[i][d] / T[d][d];
                FOR(j, d, n+1)	T[i][j] -= T[d][j] * val;
            }
            val = T[d][d];
            FOR(j, d, n+1)	T[d][j] /= val;  
        }
        for (int d=n-1; d>=0; d--)
        {
            if (T[d][d] == 0)
            {
                if (T[d][n] != 0)   return 0;
                resUnique = false;
            }
        }
        return resUnique ? 1 : 2;
    }
};
