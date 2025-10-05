struct Miller_rabin_test
{	
	long long mod;
    bool witness(long long w)
    {
    	long long x = mod - 1, prev = x, k = __builtin_ctzll(x);
        __int128_t a = qpow(w, x>>k);
        while (a != 1 and k--)
        	prev = a, a = a * a % mod;
       	return prev != x or a != 1;
    }
    bool prime(long long n)
    {
        if (n < 2)  return false;	if (n < 4)  return true;
        mod = n;	int s = 15;
        while (s--)
        {
            long long a = 1;
            while (a == 1 or a % 2 == 0)	a = 1ll*rand()*rand()%n;
            if (witness(a))	return false;
        }
        return true;
    }
};
