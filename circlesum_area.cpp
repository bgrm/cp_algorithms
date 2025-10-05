long double get_ang(long double a, long double b, long double c)
{	return acos((kw(b) + kw(c) - kw(a)) / (b*c*2));	}

long double CircCutArea(long double x[2], long double y[2], long double r[2])
{
	long double d = kw(x[0]-x[1]) + kw(y[0]-y[1]);
	if (d <= kw(r[0]-r[1]))
		return M_PI * kw(min(r[0],r[1]));
		
	if (d >= kw(r[0]+r[1]))
		return 0;

	long double res = 0;
	FOR(i, 0, 2)
	{
		long double ang = get_ang(r[i^1], r[i], sqrtl(d)) * 2;
		res += (ang - sin(ang)) * kw(r[i]);
	}
	res /= 2;
	return res;
}

