struct Dio
{
	long long chopy(long long a, long long b, long long m)
	{
		if (b < 0)	a *= -1, b *= -1;
		long long res = 0;
		for (; b; b>>=1)
		{
			if (b & 1)	res = (res + a) % m;
			a = a * 2 % m;
		}
		return res;
	}
	bool diophEq(long long a, long long b, long long c, long long& x, long long& y)
	{
		if (a == 0 and b == 0)
		{	x = y = 0;	return c == 0;	}
		if (a == 0 or b == 0)
		{
			x = y = c / max(a, b);
			return c % max(a, b) == 0;
		}
		long long g = extEuc(a, b, x, y);
		if (c % g != 0)	return false;
		long long dx = c / a;
		c -= dx * a;
		long long dy = c / b;
		c -= dy * b;
		x = dx + chopy(x, c / g, b);
		y = dy + chopy(y, c / g, a);
		long long p = y - x, q = (a + b) / g;
		long long k = (p < 0 and p % q != 0) ? p / q - 1 : p / q;	
		x += b / g * k;  y -= a / g * k;
		if (llabs(x - y + (a + b) / g) < llabs(x - y))
			x += b / g, y -= a / g;
		return true;	
	}
};
