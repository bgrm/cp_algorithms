vector <pair <int, long long> > SternBrocotPath(long long x, long long y)
{
	int s = 0;
	vector <pair <int, long long> > ret;
	if (x > y)	swap(x, y), s = 1;
	while (x != 0)
		ret.pb({s, y/x}), y %= x, swap(x, y), s ^= 1;
	ret.back().sd--;
	return ret;
}
