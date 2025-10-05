struct Discrete_Logarithm
{
    pair <long long, int> t[maxD];
    int discrete(long long a, long long b)
    {
        int d = sqrt(mod) + 42;
        t[0] = {1, 0};
		FOR(i, 1, d+1)	t[i] = {t[i - 1].first * a % mod, i};
        t[d].first = qpow(t[d].first, mod-2);
        sort(t, t + d);
        FOR(i, 0, d)
        {
            auto find = lower_bound(t, t + d, make_pair(b, 0));
            if (find != t + d and find->first == b)
                return (d * i + find->second);
			b = b * t[d].first % mod;
        }
        return -1;
    }
};
