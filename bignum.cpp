struct BigNum
{
	static const int B = 1000000000;
	vector <int> a;		int sign;
	void normalise()
	{
		while (a.size() != 1 and a.back() == 0)	a.pop_back();
		if (a.back() == 0)	sign = 1;
	}
	int operator[] (int i)	const	{	return a[i];	}	
	bool lowerMod(const BigNum& other)	const
	{
		if (a.size() != other.a.size())
			return a.size() < other.a.size();
		for (int i=a.size()-1; i>=0; i--)
			if (a[i] != other[i])
				return a[i] < other[i];
		return false;
	}		
	void operator+= (BigNum& other)
	{
		if (other.sign != sign)
		{
			other.sign *= -1;	(*this) -= other;
			other.sign *= -1;	return;
		}
		a.resize(max(a.size(), other.a.size()));
		int carry = 0;
		FOR(i, 0, a.size())
		{
			int b = a[i] + carry + (i < other.a.size() ? other[i] : 0);
			a[i] = b % B;
			carry = b >= B;
		}
		if (carry == 1)	a.pb(1);
	}
	void operator-= (BigNum& other)
	{
		if (sign != other.sign)
		{
			other.sign *= -1;	(*this) -= other;
			other.sign *= -1;	return;
		}
		bool inv = lowerMod(other);
		vector <int>& x = inv ? other.a : a;
		vector <int>& y = inv ? a : other.a;
		a.resize(x.size());
		int carry = 0;
		FOR(i, 0, a.size())
		{
			a[i] = x[i] - carry - (i < y.size() ? y[i] : 0);
			if (carry = (a[i] < 0))		a[i] += B;
		}
		if (inv) sign = -sign;
		normalise();
	}
	void operator/= (int m)	//|m|<B
	{
		if (m < 0)	m = -m, sign = -sign;
		long long mod = 0;
		for (int i=a.size()-1; i>=0; i--)
		{
			mod = mod * B + a[i];
			a[i] = mod / m;
			mod %= m;
		}
		normalise();
		if (sign == -1 and mod != 0)
		{
			BigNum mOne(-1ll);
			(*this) += mOne;
		}
	}
	BigNum operator* (BigNum& other)
	{
		BigNum res(0);
		vector <int> &b = other.a, &c = res.a;
		c.resize(a.size() + b.size());
		FOR(i, 0, a.size()) FOR(j, 0, b.size())
		{
			long long x = 1ll * a[i] * b[j] + c[i+j];
			c[i+j] = x % B;
			c[i+j+1] += x / B;
		}
		res.sign = sign * other.sign;
		res.normalise();
		return res;
	}
	int operator% (int m)
	{
		long long b = 1;
		int res = 0;
		FOR(i, 0, a.size())
			res = (b * a[i] + res) % m, b = b * B % m;
		if (sign == -1 and res != 0)	res = m - res;
		return res;
	}
	bool operator< (const BigNum& other)
	{
		if (sign != other.sign)	return sign < other.sign;
		return sign == 1 ? lowerMod(other) : other.lowerMod(*this);
	}
	void operator= (char* s)
	{
		sign = 1; a.resize(0);
		if (s[0] == '-')	sign = -1, s++;
		int m = strlen(s);
		for (int i=m; i>0; i-=9)
		{
			int j=max(0, i-9);	swap(s[i], s[m]);
			a.pb(atoi(s+j));	swap(s[i], s[m]);
		}
		normalise();
	}
	void operator= (long long n)
	{
		sign = 1;
		if (n < 0)	sign = -1, n *= -1;
		a.resize(0);
		if (n == 0)	a.pb(0);
		for (; n != 0; n /= B)	a.pb(n % B);
	}
	void operator= (const BigNum& other)
	{	sign = other.sign; a = other.a;	}
	BigNum(long long n)		{	(*this) = n;	}
	BigNum operator+ (BigNum& other)
	{	BigNum res(*this);	res += other; return res;	}
};
