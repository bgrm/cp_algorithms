template <typename Tp> struct Point_t
{
	Tp x, y;	int ind;
	Point_t (Tp a = 0, Tp b = 0, int i = 0)
		: x(a), y(b), ind(i) {}
	
	Tp operator% 	(const Point_t& he) 	const	{	return x * he.y - he.x * y;	}
	Point_t operator- (const Point_t& he)	const	{	return Point_t(x - he.x, y - he.y, ind);	}
	Tp len2()	const{	return x*x + y*y;	}
	bool operator< (const Point_t& he)	const
	{
		Tp ilo = (*this) % he;
		if (ilo != 0)			return ilo > 0;
		if (y != 0 or he.y != 0)return y < he.y;
		return x < he.x;
	}
};  typedef Point_t <long long> Point;
int bottomLeftInd(vector <Point>& T)
{
	int j = 0;
	FOR(i, 1, T.size())
		if (T[i].y < T[j].y or (T[i].y == T[j].y and T[i].x < T[j].x))
			j = i;
	return j;
}		
vector <Point> convex(vector <Point>& P)
{
	Point mv = P[bottomLeftInd(P)];
	FOR(i, 0, P.size())
		P[i] = P[i] - mv;
	sort(ALL(P));
	vector <Point> res(1, P[0]);
	FOR(i, 1, P.size())
	{	
		#define LAST(i) res[res.size() - (i)]
		while (res.size() > 1 and (LAST(1) - LAST(2)) % (P[i] - LAST(2)) <= 0)
			res.pop_back();
		res.pb(P[i]);
	}
	return res;
}
pair <int, int> perimeter(vector <Point>& C)
{
	pair <int, int> res = {0, 1};
	if (C.size() == 2)	return res;
	int j = 1;	C.pb(C[0]);
	Tp dst2 = 0;
	FOR(i, 1, C.size())
	{
		T a = C[i].y - C[i-1].y, b = C[i-1].x - C[i].x, c = -a*C[i].x - b*C[i].y;
		#define DIST(k)	abs(a * C[k].x + b * C[k].y + c)
		#define NX(k)	((k+1) % C.size())
		while (DIST(NX(j)) >= DIST(j))	j = NX(j);
		Tp cand = (C[i] - C[j]).len2();
		if (dst2 < cand)
			dst2 = cand, res = {i, j};
	}
	C.pop_back();
	res.first %= C.size();
	return res;
}

Tp sgn(Tp a)
{	return a >> 63-__builtin_clzll(a);	}
long long dir(const Point& a, const Point& b, const Point& c)
{	return sgn((b - a) % (c - a));	}
bool intersect(const Segment& A, const Segment& B)
{
	#define I(a) a.first
	#define II(a) a.second
	long long prod[4] = {
		dir(I(A), II(A), I(B)),
		dir(I(A), II(A), II(B)),
		dir(I(B), II(B), I(A)),
		dir(I(B), II(B), II(A)),
	};
	if (prod[0] | prod[1])
		return prod[0] == prod[1] or prod[2] == prod[3];
	#define BETW(a, b, c) (min(b, c) <= (a) and (a) <= max(b, c))
	#define BETWpt(a, b, c) (BETW(a.x, b.x, c.x) and BETW(a.y, b.y, c.y))
	return
	BETWpt(I(A),  I(B), II(B)) or
	BETWpt(II(A), I(B), II(B)) or
	BETWpt(I(B),  I(A), II(A)) or
	BETWpt(II(B), I(A), II(A));
}
