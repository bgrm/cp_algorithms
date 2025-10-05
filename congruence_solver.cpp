struct Congruence_solver
{
    long long extGcd(long long a, long long b, long long& x, long long& y)
	{
		if (b == 0)
		{   x = 1; y = 0; return a;	}
		long long gcd = extGcd(b, a % b, y, x);
		y -= a / b * x;
		return gcd;
	}
    pair <long long, long long> congruence_solver(long long* r, long long* mod, int n)
    {
        long long restGlobal = 0, modGlobal = 1;
        FOR(i, 0, n)
        {
            long long x, y, gcd = extGcd(modGlobal, mod[i], x, y);
            if ((restGlobal - r[i]) % gcd != 0)	return {0, 0};

            long long m1 = modGlobal / gcd, m2 = mod[i] / gcd;
            modGlobal = m1 * m2 * gcd;
			restGlobal = restGlobal * m2 * y + r[i] * m1 * x;
			restGlobal = myMod(restGlobal, modGlobal);
        }
        return {restGlobal, modGlobal};
    }
};
