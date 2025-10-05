struct LinearExtremes
{
typedef pair <long long, long long> Fun;
	
	struct Rat
	{
		long long p, q;
		Rat(long long a=0, long long b=1)
		{
			long long c = __gcd(a, b);
			p = a / c, q = b / c;
			if (q < 0)	p = -p, q = -q;
		}
		Rat operator-()	const
		{	return Rat(-p, q);	}
		
		bool operator< (const Rat& he)	const
		{
			if ((p >= 0) xor (he.p >= 0))
				return p < he.p;
			if (p < 0)
				return -he < -(*this);
				
			long long w1 = p / q, w2 = he.p / he.q;
			if (w1 != w2) return w1 < w2;
			
			w1 = p % q, w2 = he.p % he.q;
			return w1 * he.q < w2 * q;			
		}
		bool operator<= (const Rat& he)	const
		{	return !(he < *this);	}
	};
	
	struct HL
	{
		Fun f;
		mutable Rat x;
		HL(Fun g={0,0}, Rat y=Rat(0))
		:	f(g), x(y)	{};
		
		bool operator< (const HL& he)const { return f < he.f; }
		bool operator< (const Fun& he)const{ return f < he; }
		bool operator< (const Rat& he)const{ return x < he; }
	};
	
	bool maxi;
	set <HL, less<>> H;
	const Rat mINF = Rat(-INF);
	
	Rat cutx(const Fun& f, const Fun& g)
	{	return Rat(f.sd - g.sd, g.ft - f.ft);	}

	void init(vector <Fun>& T, bool _maxi = true)
	{
		maxi = _maxi;
		if (!maxi)	for (auto &f : T)
			f = {-f.ft, -f.sd};
		sort(ALL(T));
		vector <HL> hull(0);
		for (auto f : T)
		{
			if (!hull.empty() and hull.back().f.ft == f.ft)
				hull.pop_back();
			
			#define CUTWithLast cutx(hull.back().f, f)
			
			while (!hull.empty() and CUTWithLast <= hull.back().x)
				hull.pop_back();		
			Rat x = hull.empty() ? mINF : CUTWithLast;
			hull.pb(HL(f, x));
		}
		H = set <HL, less<>> (ALL(hull));

		if (!maxi)	for (auto &f : T)
			f = {-f.ft, -f.sd};
	}
	bool valid(auto it)
	{
		if (it == H.begin() or it == BACK(H))
			return true;
		return cutx(prev(it)->f, it->f) < cutx(it->f, next(it)->f);
	}
	void updtX(auto it)
	{	it->x = it == H.begin() ? mINF : cutx(prev(it)->f, it->f);	}
	
	void add(Fun f)
	{
		if (!maxi)	f = {-f.ft, -f.sd};
		auto it = H.insert(HL(f, 0)).ft;
		if (it != BACK(H) and next(it)->f.ft == f.ft)
		{	H.erase(it);  return;	}
		if (it != H.begin() and prev(it)->f.ft == f.ft)
			H.erase(prev(it));
		if (!valid(it))
		{	H.erase(it);  return;	}
			
		while (it != BACK(H) and !valid(next(it)))
			H.erase(next(it));
		if (it != BACK(H))
			updtX(next(it));

		while (it != H.begin() and !valid(prev(it)))
			H.erase(prev(it));
		updtX(it);
	}

	long long query(long long x)
	{
		auto ptr = H.lower_bound(Rat(x));
		Fun f = prev(ptr)->f;
		long long ret = x * f.ft + f.sd;
		return maxi ? ret : -ret;
	}	
}alg;

