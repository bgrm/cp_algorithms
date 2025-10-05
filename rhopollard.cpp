struct Rho_Pollard
{
    long long mod, c;
    vector <long long> res;
    Miller_rabin_test alg;
    long long f(__int128_t x)
    {  
    	return ((x * x - c) % mod + mod) % mod;
    }
    void go(long long n)
    {
        for (; n%2 == 0; n /= 2) res.pb(2);
        if (n <= 1000000  or  n > 1000000000000LL and alg.prime(n))
        {	res.pb(n);	return;	}
        mod = n;
        for (c=1; c<=5; c+=2)
        {
            long long x = 2, y = 2, d = 1;
            while (d == 1)
            {
                x = f(x); y = f(f(y));
                d = __gcd(llabs(x - y), n);
            }           
            if (d < n)
            {	go(d); go(n / d);  return;	}
        }
        res.pb(n);
    }
    vector <long long> rhopollard(long long n)	
    {
        res.clear();
        if (n < 2)  return res;
        go(n);
        sort(ALL(res));
        return res;
    }
};
